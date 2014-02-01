#include <cassert>
#include <cmath>

#include "player.h"
#include "animated_sprite.h"
#include "graphics.h"
#include "game.h"
#include "map.h"
#include "rectangle.h"

// Walk Motion
const double kSlowdownFactor{0.8};
const double kWalkingAcceleration{0.0012}; // (pixels/ms) / ms
const double kMaxSpeedX{0.325};            // pixels / ms
// Fall Motion
const double kMaxSpeedY{0.2998046875};     // pixels / ms
const double kGravity{0.00078125};         // (pixels / ms) / ms
// Jump Motion
const double kAirAcceleration{0.0003125};  // pixels / ms / ms
const double kJumpSpeed{0.25};             // pixels / ms
const double kJumpGravity{0.0003125};      // pixels / ms / ms
// Sprites
const std::string kSpriteFilePath{"content/MyChar.bmp"};
// Sprite Frames
const int kCharacterFrame{0};

const int kWalkFrame{0};
const int kStandFrame{0};
const int kJumpFrame{1};
const int kFallFrame{2};

const int kUpFrameOffset{3};
const int kDownFrame{6};
const int kBackFrame{7};
// Walk Anumation
const int kNumWalkFrames{3};
const int kWalkFps{15};

//Collision rectangle
const Rectangle kCollisionX{6, 10, 20, 12};
const Rectangle kCollisionY{10, 2, 12, 30};

namespace {

struct CollisionInfo {
    bool collided;
    int row;
    int col;
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

Player::Player(Graphics& graphics, Vector<int> pos) :
    pos_(pos),
    velocity_{0.0, 0.0},
    acceleration_x_direction_{0},
    horizontal_facing_{HorizontalFacing::LEFT},
    vertical_facing_{VerticalFacing::HORIZONTAL},
    is_on_ground_{false},
    is_jump_active_{false},
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
}

void Player::startMovingRight()
{
    horizontal_facing_ = HorizontalFacing::RIGHT;
    acceleration_x_direction_ = 1;
}

void Player::stopMoving()
{
    acceleration_x_direction_ = 0;
}

void Player::lookUp()
{
    vertical_facing_ = VerticalFacing::UP;
}

void Player::lookDown()
{
    vertical_facing_ = VerticalFacing::DOWN;
}

void Player::lookHorizontal()
{
    vertical_facing_ = VerticalFacing::HORIZONTAL;
}

void Player::startJump()
{
    is_jump_active_ = true;
    if (is_on_ground()) {
        velocity_.y = -kJumpSpeed;
    }
}

void Player::stopJump()
{
    is_jump_active_ = false;
}

int Player::getFrameY(const SpriteState& s) const
{
    int source_y = (s.horizontal_facing == HorizontalFacing::LEFT)
        ? 2 * kCharacterFrame * Game::kTileSize
        : (1 + 2 * kCharacterFrame) * Game::kTileSize;
    return source_y;
}

int Player::getFrameX(const SpriteState& s) const
{
    int source_x{0};
    switch (s.motion_type) {
    case MotionType::WALKING:
        source_x = kWalkFrame * Game::kTileSize;
        break;
    case MotionType::STANDING:
        source_x = kStandFrame * Game::kTileSize;
        break;
    case MotionType::JUMPING:
        source_x = kJumpFrame * Game::kTileSize;
        break;
    case MotionType::FALLING:
        source_x = kFallFrame * Game::kTileSize;
        break;
    case MotionType::LAST_MOTION_TYPE:
        break;
    }

    if (s.vertical_facing == VerticalFacing::UP) {
        source_x += kUpFrameOffset * Game::kTileSize;
    } else if (s.vertical_facing == VerticalFacing::DOWN) {
        source_x = s.motion_type == MotionType::STANDING
            ? kBackFrame * Game::kTileSize
            : kDownFrame * Game::kTileSize;
    }

    return source_x;
}

void Player::initializeSprite(Graphics& graphics,
        const SpriteState& sprite_state)
{
    int source_y = getFrameY(sprite_state);
    int source_x = getFrameX(sprite_state);

    if (sprite_state.motion_type == MotionType::WALKING) {
        sprites_[sprite_state] = std::unique_ptr<Sprite>{
            new AnimatedSprite(
                    graphics,
                    kSpriteFilePath,
                    source_x, source_y, Game::kTileSize, Game::kTileSize,
                    kWalkFps, kNumWalkFrames
                    )
        };
    } else {
        sprites_[sprite_state] = std::unique_ptr<Sprite>{
            new Sprite(
                    graphics,
                    kSpriteFilePath,
                    source_x, source_y,
                    Game::kTileSize, Game::kTileSize
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
    if (is_on_ground()) {
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

Rectangle Player::leftCollision(int delta) const
{
    assert(delta <= 0);
    return Rectangle(
            pos_.x + kCollisionX.getLeft() + delta,
            pos_.y + kCollisionX.getTop(),
            kCollisionX.getWidth() / 2 - delta,
            kCollisionX.getHeight()
            );
}

Rectangle Player::rightCollision(int delta) const
{
    assert(delta >= 0);
    return Rectangle(
            pos_.x + kCollisionX.getLeft() + kCollisionX.getWidth() / 2,
            pos_.y + kCollisionX.getTop(),
            kCollisionX.getWidth() / 2 + delta,
            kCollisionX.getHeight()
            );
}

Rectangle Player::topCollision(int delta) const
{
    assert(delta <= 0);
    return Rectangle(
            pos_.x + kCollisionY.getLeft(),
            pos_.y + kCollisionY.getTop() + delta,
            kCollisionY.getWidth(),
            kCollisionY.getHeight() / 2 - delta
            );
}

Rectangle Player::bottomCollision(int delta) const
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
    double acceleration_x{0.0};
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
        velocity_.x *= kSlowdownFactor;
    }
    // Calculate delta
    const int delta = (int)round(velocity_.x * elapsed_time.count());
    if (delta > 0) {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map, rightCollision(delta));
        // React to collision
        if (info.collided) {
            pos_.x = info.col * Game::kTileSize - kCollisionX.getRight();
            velocity_.x = 0.0;
        } else {
            pos_.x += delta;
        }
        // Check collision in the direction opposite to delta
        info = getWallCollisionInfo(map, leftCollision(0));
        if (info.collided) {
            pos_.x = info.col * Game::kTileSize + kCollisionX.getRight();
        }
    } else {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map, leftCollision(delta));
        // React to collision
        if (info.collided) {
            pos_.x = info.col * Game::kTileSize + kCollisionX.getRight();
            velocity_.x = 0.0;
        } else {
            pos_.x += delta;
        }
        // Check collision in the direction opposite to delta
        info = getWallCollisionInfo(map, rightCollision(0));
        if (info.collided) {
            pos_.x = info.col * Game::kTileSize - kCollisionX.getRight();
        }
    }
}

void Player::updateY(std::chrono::milliseconds elapsed_time, const Map& map)
{
    // Update velocity
    const double gravity = is_jump_active_ && velocity_.y < 0
        ? kJumpGravity
        : kGravity;
    velocity_.y = std::min(velocity_.y + gravity * elapsed_time.count(),
                kMaxSpeedY);
    // Calculate delta
    const int delta = (int)round(velocity_.y * elapsed_time.count());
    if (delta > 0) {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map, bottomCollision(delta));
        // React to collision
        if (info.collided) {
            pos_.y = info.row * Game::kTileSize - kCollisionY.getBottom();
            velocity_.y = 0.0;
            is_on_ground_ = true;
        } else {
            pos_.y += delta;
            is_on_ground_ = false;
        }
        // Check collision in the direction opposite to delta
        info = getWallCollisionInfo(map, topCollision(0));
        if (info.collided) {
            pos_.y = info.row * Game::kTileSize + kCollisionY.getHeight();
        }
    } else {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map, topCollision(delta));
        // React to collision
        if (info.collided) {
            pos_.y = info.row * Game::kTileSize + kCollisionY.getHeight();
            velocity_.y = 0.0;
        } else {
            pos_.y += delta;
            is_on_ground_ = false;
        }
        // Check collision in the direction opposite to delta
        info = getWallCollisionInfo(map, bottomCollision(0));
        if (info.collided) {
            pos_.y = info.row * Game::kTileSize - kCollisionY.getBottom();
            is_on_ground_ = true;
        }
    }
}
