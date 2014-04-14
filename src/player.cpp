#include <cassert>
#include <cmath>

#include "player.h"
#include "animated_sprite.h"
#include "number_sprite.h"
#include "graphics.h"
#include "game.h"
#include "map.h"
#include "rectangle.h"

// Walk Motion
const units::Acceleration kWalkingAcceleration{0.00083007812};
const units::Acceleration kFriction{0.00049804687};
const units::Velocity kMaxSpeedX{0.15859375};
// Fall Motion
const units::Acceleration kGravity{0.00078125};
const units::Velocity kMaxSpeedY{0.2998046875};
// Jump Motion
const units::Acceleration kAirAcceleration{0.0003125};
const units::Acceleration kJumpGravity{0.0003125};
const units::Velocity kJumpSpeed{0.25};
const units::Velocity kShortJumpSpeed{kJumpSpeed / 1.5};
// Sprites
const std::string kPlayerSpriteFilePath{"MyChar"};
// Sprite Frames
const units::Frame kCharacterFrame{0};

const units::Frame kWalkFrame{0};
const units::Frame kStandFrame{0};
const units::Frame kJumpFrame{1};
const units::Frame kFallFrame{2};

const units::Frame kUpFrameOffset{3};
const units::Frame kLeftFrameOffset{1};
const units::Frame kRightFrameOffset{2};
const units::Frame kDownFrame{6};
const units::Frame kBackFrame{7};

//Collision rectangles
const Rectangle kCollisionX{ 6, 10, 20, 12 };
const Rectangle kCollisionY{ 10, 2, 12, 30 };

const std::chrono::milliseconds kInvincibleFlashTime{50};
const std::chrono::milliseconds kInvincibleTime{3000};

namespace {

struct CollisionInfo {
    bool collided;
    units::Tile row;
    units::Tile col;
};
CollisionInfo getWallCollisionInfo(const Map& map, const Rectangle& rect) {
    CollisionInfo info{false, 0, 0};
    std::vector<Map::CollisionTile> tiles(map.getCollidingTiles(rect));
    for (auto &tile : tiles) {
        if (tile.tile_type == Map::TileType::WALL) {
            info = {true, tile.row, tile.col};
            break;
        }
    }
    return info;
}

} // anonymous namespace

Player::Player(Graphics& graphics, Vector<units::Game> pos) :
    pos_(pos),
    velocity_{0.0, 0.0},
    acceleration_x_direction_{0},
    horizontal_facing_{HorizontalFacing::LEFT},
    intended_vertical_facing_{VerticalFacing::HORIZONTAL},
    is_on_ground_{false},
    is_jump_active_{false},
    is_interacting_{false},
    health_(graphics),
    invincible_timer_{kInvincibleTime},
    damage_text_(new DamageText()),
    walking_animation_(),
    polar_star_(graphics),
    sprites_()
{
    initializeSprites(graphics);
}

Player::~Player() {}

void Player::update(const std::chrono::milliseconds elapsed_time,
        const Map& map)
{
    sprites_[getSpriteState()]->update();

    health_.update();
    walking_animation_.update();

    polar_star_.updateProjectiles(elapsed_time, map);

    updateX(elapsed_time, map);
    updateY(elapsed_time, map);
}

void Player::draw(Graphics& graphics) const
{
    if (spriteIsVisible()) {
        polar_star_.draw(
                graphics,
                horizontal_facing_,
                vertical_facing(),
                is_gun_up(),
                pos_
                );
        sprites_.at(getSpriteState())->draw(graphics, pos_);
    }
}

void Player::drawHUD(Graphics& graphics) const
{
    if (spriteIsVisible()) {
        health_.draw(graphics);
    }
}

void Player::startMovingLeft()
{
    if (is_on_ground() && acceleration_x_direction_ == 0) {
        walking_animation_.reset();
    }
    horizontal_facing_ = HorizontalFacing::LEFT;
    acceleration_x_direction_ = -1;
    is_interacting_ = false;
}

void Player::startMovingRight()
{
    if (is_on_ground() && acceleration_x_direction_ == 0) {
        walking_animation_.reset();
    }
    horizontal_facing_ = HorizontalFacing::RIGHT;
    acceleration_x_direction_ = 1;
    is_interacting_ = false;
}

void Player::stopMoving()
{
    acceleration_x_direction_ = 0;
}

void Player::lookUp()
{
    intended_vertical_facing_ = VerticalFacing::UP;
    is_interacting_ = false;
}

void Player::lookDown()
{
    if (intended_vertical_facing_ == VerticalFacing::DOWN) return;
    intended_vertical_facing_ = VerticalFacing::DOWN;
    is_interacting_ = is_on_ground();
}

void Player::lookHorizontal()
{
    intended_vertical_facing_ = VerticalFacing::HORIZONTAL;
}

void Player::startJump()
{
    is_interacting_ = false;
    is_jump_active_ = true;
    if (is_on_ground()) {
        velocity_.y = -kJumpSpeed;
    }
}

void Player::stopJump()
{
    is_jump_active_ = false;
}

void Player::startFire()
{
    polar_star_.startFire(
            pos_,
            horizontal_facing_,
            intended_vertical_facing_,
            is_gun_up()
            );
}

void Player::stopFire()
{
    polar_star_.stopFire();
}

void Player::takeDamage(units::HP damage) {
    if (invincible_timer_.is_active()) return;

    velocity_.y = std::min(velocity_.y, -kShortJumpSpeed);
    invincible_timer_.reset();
    health_.takeDamage(damage);
    damage_text_->setDamage(damage);
}

const Rectangle Player::getDamageRectangle() const
{
    return Rectangle(pos_.x + kCollisionX.getLeft(),
            pos_.y + kCollisionY.getTop(),
            kCollisionX.getWidth(),
            kCollisionY.getHeight());
}

const Vector<units::Game> Player::getCenterPos() const
{
    return Vector<units::Game> {
        pos_.x + units::kHalfTile,
        pos_.y + units::kHalfTile
    };
}

const std::shared_ptr<DamageText> Player::getDamageText() const
{
    return damage_text_;
}

std::vector<std::shared_ptr<GenericProjectile> > Player::getProjectiles()
{
    return polar_star_.getProjectiles();
}

bool Player::is_gun_up() const
{
    return (getMotionType() == MotionType::WALKING)
        && (walking_animation_.stride() != StrideType::MIDDLE);
}

units::Tile Player::getFrameY(const SpriteState& s) const
{
    units::Tile tile_y = (s.horizontal_facing == HorizontalFacing::LEFT)
        ? 2 * kCharacterFrame
        : 1 + 2 * kCharacterFrame;
    return tile_y;
}

units::Tile Player::getFrameX(const SpriteState& s) const
{
    units::Tile tile_x{0};
    switch (s.motion_type) {
    case MotionType::WALKING:
        tile_x = kWalkFrame;

        switch (s.stride_type) {
        case StrideType::MIDDLE:
            break;
        case StrideType::LEFT:
            tile_x += kLeftFrameOffset;
            break;
        case StrideType::RIGHT:
            tile_x += kRightFrameOffset;
            break;
        default:
            break;
        }

        break;
    case MotionType::STANDING:
        tile_x = kStandFrame;
        break;
    case MotionType::INTERACTING:
        tile_x = kBackFrame;
        break;
    case MotionType::JUMPING:
        tile_x = kJumpFrame;
        break;
    case MotionType::FALLING:
        tile_x = kFallFrame;
        break;
    case MotionType::LAST_MOTION_TYPE:
        break;
    }
    switch (s.vertical_facing) {
    case VerticalFacing::HORIZONTAL:
        break;
    case VerticalFacing::UP:
        tile_x += kUpFrameOffset;
        break;
    case VerticalFacing::DOWN:
        tile_x = kDownFrame;
        break;
    default:
        break;
    }

    return tile_x;
}

void Player::initializeSprite(Graphics& graphics,
        const SpriteState& sprite_state)
{
    units::Tile tile_y = getFrameY(sprite_state);
    units::Tile tile_x = getFrameX(sprite_state);

    sprites_[sprite_state] = std::unique_ptr<Sprite>{
        new Sprite(
                graphics,
                kPlayerSpriteFilePath,
                units::tileToPixel(tile_x), units::tileToPixel(tile_y),
                units::tileToPixel(1), units::tileToPixel(1)
                )
    };
}

void Player::initializeSprites(Graphics& graphics)
{
    ENUM_FOREACH(m, MotionType, MOTION_TYPE) {
        ENUM_FOREACH(h, HorizontalFacing, HORIZONTAL_FACING) {
            ENUM_FOREACH(v, VerticalFacing, VERTICAL_FACING) {
                ENUM_FOREACH(s, StrideType, STRIDE_TYPE) {
                    MotionType mtype = (MotionType)m;
                    HorizontalFacing hfacing = (HorizontalFacing)h;
                    VerticalFacing vfacing = (VerticalFacing)v;
                    StrideType stride = (StrideType)s;

                    auto sprite = SpriteState(mtype, hfacing, vfacing, stride);

                    initializeSprite(graphics, sprite);
                }
            }
        }
    }
}

Player::MotionType Player::getMotionType() const
{
    MotionType motion;
    if (is_interacting_) {
        motion = MotionType::INTERACTING;
    } else if (is_on_ground()) {
        motion = acceleration_x_direction_ == 0
            ? MotionType::STANDING
            : MotionType::WALKING;
    } else {
        motion = velocity_.y < 0.0
            ? MotionType::JUMPING
            : MotionType::FALLING;
    }
    return motion;
}

bool Player::is_on_ground() const
{
    return is_on_ground_;
}

VerticalFacing Player::vertical_facing() const
{
    if (is_on_ground() && intended_vertical_facing_ == VerticalFacing::DOWN) {
        return VerticalFacing::HORIZONTAL;
    } else {
        return intended_vertical_facing_;
    }
}

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b)
{
    auto atie = std::tie(
            a.motion_type, 
            a.horizontal_facing, 
            a.vertical_facing,
            a.stride_type
            );
    auto btie = std::tie(
            b.motion_type, 
            b.horizontal_facing, 
            b.vertical_facing,
            b.stride_type
            );
    return atie < btie;
}

const Player::SpriteState Player::getSpriteState() const
{
    return SpriteState(
            getMotionType(),
            horizontal_facing_,
            vertical_facing(),
            walking_animation_.stride()
            );
}

const Rectangle Player::leftCollision(units::Game delta) const
{
    assert(delta <= 0 && "Wrong delta value");
    return Rectangle(
            pos_.x + kCollisionX.getLeft() + delta,
            pos_.y + kCollisionX.getTop(),
            kCollisionX.getWidth() / 2 - delta,
            kCollisionX.getHeight()
            );
}

const Rectangle Player::rightCollision(units::Game delta) const
{
    assert(delta >= 0 && "Wrong delta value");
    return Rectangle(
            pos_.x + kCollisionX.getLeft() + kCollisionX.getWidth() / 2,
            pos_.y + kCollisionX.getTop(),
            kCollisionX.getWidth() / 2 + delta,
            kCollisionX.getHeight()
            );
}

const Rectangle Player::topCollision(units::Game delta) const
{
    assert(delta <= 0 && "Wrong delta value");
    return Rectangle(
            pos_.x + kCollisionY.getLeft(),
            pos_.y + kCollisionY.getTop() + delta,
            kCollisionY.getWidth(),
            kCollisionY.getHeight() / 2 - delta
            );
}

const Rectangle Player::bottomCollision(units::Game delta) const
{
    assert(delta >= 0 && "Wrong delta value");
    return Rectangle(
            pos_.x + kCollisionY.getLeft(),
            pos_.y + kCollisionY.getTop() + kCollisionY.getHeight() / 2,
            kCollisionY.getWidth(),
            kCollisionY.getHeight() / 2 + delta
            );
}

void Player::updateX(const std::chrono::milliseconds elapsed_time,
        const Map& map)
{
    // Update velocity
    units::Acceleration acceleration_x{0.0};
    if (acceleration_x_direction_ < 0) {
        acceleration_x = is_on_ground()
            ? -kWalkingAcceleration
            : -kAirAcceleration;
    } else if (acceleration_x_direction_ > 0) {
        acceleration_x = is_on_ground()
            ? kWalkingAcceleration
            : kAirAcceleration;
    }

    velocity_.x += acceleration_x * elapsed_time.count();

    if (acceleration_x_direction_ < 0) {
        velocity_.x = std::max(velocity_.x, -kMaxSpeedX);
    } else if (acceleration_x_direction_ > 0) {
        velocity_.x = std::min(velocity_.x, kMaxSpeedX);
    } else if (is_on_ground()) {
        velocity_.x = velocity_.x > 0.0
            ? std::max(0.0, velocity_.x - kFriction * elapsed_time.count())
            : std::min(0.0, velocity_.x + kFriction * elapsed_time.count());
    }
    // Calculate delta
    const units::Game delta = velocity_.x * elapsed_time.count();

    if (delta > 0.0) {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map, rightCollision(delta));
        // React to collision
        if (info.collided) {
            pos_.x = units::tileToGame(info.col) - kCollisionX.getRight();
            velocity_.x = 0.0;
        } else {
            pos_.x += delta;
        }
        // Check collision in the direction opposite to delta
        info = getWallCollisionInfo(map, leftCollision(0));
        if (info.collided) {
            pos_.x = units::tileToGame(info.col) + kCollisionX.getRight();
        }
    } else {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map, leftCollision(delta));
        // React to collision
        if (info.collided) {
            pos_.x = units::tileToGame(info.col) + kCollisionX.getRight();
            velocity_.x = 0.0;
        } else {
            pos_.x += delta;
        }
        // Check collision in the direction opposite to delta
        info = getWallCollisionInfo(map, rightCollision(0));
        if (info.collided) {
            pos_.x = units::tileToGame(info.col) - kCollisionX.getRight();
        }
    }
}

void Player::updateY(const std::chrono::milliseconds elapsed_time,
        const Map& map)
{
    // Update velocity
    const units::Acceleration gravity = is_jump_active_ && velocity_.y < 0
        ? kJumpGravity
        : kGravity;
    velocity_.y = std::min(velocity_.y + gravity * elapsed_time.count(),
                kMaxSpeedY);
    // Calculate delta
    const units::Game delta = velocity_.y * elapsed_time.count();
    if (delta > 0.0) {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map, bottomCollision(delta));
        // React to collision
        if (info.collided) {
            pos_.y = units::tileToGame(info.row) - kCollisionY.getBottom();
            velocity_.y = 0.0;
            is_on_ground_ = true;
        } else {
            pos_.y += delta;
            is_on_ground_ = false;
        }
        // Check collision in the direction opposite to delta
        info = getWallCollisionInfo(map, topCollision(0));
        if (info.collided) {
            pos_.y = units::tileToGame(info.row) + kCollisionY.getHeight();
        }
    } else {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map, topCollision(delta));
        // React to collision
        if (info.collided) {
            pos_.y = units::tileToGame(info.row) + kCollisionY.getHeight();
            velocity_.y = 0.0;
        } else {
            pos_.y += delta;
            is_on_ground_ = false;
        }
        // Check collision in the direction opposite to delta
        info = getWallCollisionInfo(map, bottomCollision(0));
        if (info.collided) {
            pos_.y = units::tileToGame(info.row) - kCollisionY.getBottom();
            is_on_ground_ = true;
        }
    }
}

bool Player::spriteIsVisible() const
{
    return !(invincible_timer_.is_active() &&
            invincible_timer_.current_time() / kInvincibleFlashTime % 2 == 0);
}
