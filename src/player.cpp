#include <cassert>
#include <cmath>

#include "player.h"
#include "animated_sprite.h"
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
// Sprites
const std::string kSpriteFilePath{"content/MyChar.bmp"};
// Sprite Frames
const units::Frame kCharacterFrame{0};

const units::Frame kWalkFrame{0};
const units::Frame kStandFrame{0};
const units::Frame kJumpFrame{1};
const units::Frame kFallFrame{2};

const units::Frame kUpFrameOffset{3};
const units::Frame kDownFrame{6};
const units::Frame kBackFrame{7};
// Walk Anumation
const units::Frame kNumWalkFrames{3};
const units::FPS kWalkFps{15};

//Collision rectangles
const Rectangle kCollisionX{ 6, 10, 20, 12 };
const Rectangle kCollisionY{ 10, 2, 12, 30 };

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

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b)
{
    return std::tie(a.motion_type, a.horizontal_facing, a.vertical_facing) <
            std::tie(b.motion_type, b.horizontal_facing, b.vertical_facing);
}

Player::Player(Graphics& graphics, Vector<units::Game> pos) :
    pos_(pos),
    velocity_{0.0, 0.0},
    acceleration_x_direction_{0},
    horizontal_facing_{HorizontalFacing::LEFT},
    vertical_facing_{VerticalFacing::HORIZONTAL},
    is_on_ground_{false},
    is_jump_active_{false},
    is_interacting_{false},
    sprites_()
{
    initializeSprites(graphics);
}

Player::~Player()
{
    ;
}

void Player::update(std::chrono::milliseconds elapsed_time, const Map& map)
{
    sprites_[getSpriteState()]->update(elapsed_time);

    updateX(elapsed_time, map);
    updateY(elapsed_time, map);
}

void Player::draw(Graphics& graphics)
{
    sprites_[getSpriteState()]->draw(graphics, pos_);
}

void Player::startMovingLeft()
{
    horizontal_facing_ = HorizontalFacing::LEFT;
    acceleration_x_direction_ = -1;
    is_interacting_ = false;
}

void Player::startMovingRight()
{
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
    vertical_facing_ = VerticalFacing::UP;
    is_interacting_ = false;
}

void Player::lookDown()
{
    if (vertical_facing_ == VerticalFacing::DOWN) return;
    vertical_facing_ = VerticalFacing::DOWN;
    is_interacting_ = is_on_ground();
}

void Player::lookHorizontal()
{
    vertical_facing_ = VerticalFacing::HORIZONTAL;
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

    if (s.vertical_facing == VerticalFacing::UP) {
        tile_x += kUpFrameOffset;
    } else if (s.vertical_facing == VerticalFacing::DOWN &&
               (s.motion_type == MotionType::JUMPING
             || s.motion_type == MotionType::FALLING)) {
            tile_x = kDownFrame;
    }
    return tile_x;
}

void Player::initializeSprite(Graphics& graphics,
        const SpriteState& sprite_state)
{
    units::Tile tile_y = getFrameY(sprite_state);
    units::Tile tile_x = getFrameX(sprite_state);

    if (sprite_state.motion_type == MotionType::WALKING) {
        sprites_[sprite_state] = std::unique_ptr<Sprite>{
            new AnimatedSprite(
                    graphics,
                    kSpriteFilePath,
                    units::tileToPixel(tile_x), units::tileToPixel(tile_y),
                    units::tileToPixel(1), units::tileToPixel(1),
                    kWalkFps, kNumWalkFrames
                    )
        };
    } else {
        sprites_[sprite_state] = std::unique_ptr<Sprite>{
            new Sprite(
                    graphics,
                    kSpriteFilePath,
                    units::tileToPixel(tile_x), units::tileToPixel(tile_y),
                    units::tileToPixel(1), units::tileToPixel(1)
                    )
        };
    }
}

void Player::initializeSprites(Graphics& graphics)
{
    for (int m = (int)(MotionType::FIRST_MOTION_TYPE);
            m < (int)(MotionType::LAST_MOTION_TYPE);
            ++m)
        for (int h = (int)(HorizontalFacing::FIRST_HORIZONTAL_FACING);
                h < (int)(HorizontalFacing::LAST_HORIZONTAL_FACING);
                ++h)
            for (int v = (int)(VerticalFacing::FIRST_VERTICAL_FACING);
                    v < (int)(VerticalFacing::LAST_VERTICAL_FACING);
                    ++v) {
                MotionType motion_type = (MotionType)m;
                HorizontalFacing horiz_facing = (HorizontalFacing)h;
                VerticalFacing vert_facing = (VerticalFacing)v;

                initializeSprite(
                        graphics,
                        SpriteState(motion_type, horiz_facing, vert_facing)
                        );
            }
}

Player::SpriteState Player::getSpriteState()
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
    return SpriteState(motion, horizontal_facing_, vertical_facing_);
}

Rectangle Player::leftCollision(units::Game delta) const
{
    assert(delta <= 0);
    return Rectangle(
            pos_.x + kCollisionX.getLeft() + delta,
            pos_.y + kCollisionX.getTop(),
            kCollisionX.getWidth() / 2 - delta,
            kCollisionX.getHeight()
            );
}

Rectangle Player::rightCollision(units::Game delta) const
{
    assert(delta >= 0);
    return Rectangle(
            pos_.x + kCollisionX.getLeft() + kCollisionX.getWidth() / 2,
            pos_.y + kCollisionX.getTop(),
            kCollisionX.getWidth() / 2 + delta,
            kCollisionX.getHeight()
            );
}

Rectangle Player::topCollision(units::Game delta) const
{
    assert(delta <= 0);
    return Rectangle(
            pos_.x + kCollisionY.getLeft(),
            pos_.y + kCollisionY.getTop() + delta,
            kCollisionY.getWidth(),
            kCollisionY.getHeight() / 2 - delta
            );
}

Rectangle Player::bottomCollision(units::Game delta) const
{
    assert(delta >= 0);
    return Rectangle(
            pos_.x + kCollisionY.getLeft(),
            pos_.y + kCollisionY.getTop() + kCollisionY.getHeight() / 2,
            kCollisionY.getWidth(),
            kCollisionY.getHeight() / 2 + delta
            );
}

void Player::updateX(std::chrono::milliseconds elapsed_time, const Map& map)
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

void Player::updateY(std::chrono::milliseconds elapsed_time, const Map& map)
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
