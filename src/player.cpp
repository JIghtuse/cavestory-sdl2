#include <cmath>

#include "player.h"
#include "animated_sprite.h"
#include "graphics.h"
#include "game.h"

// Walk Motion
const double kSlowdownFactor{0.8};
const double kWalkingAcceleration{0.0012}; // (pixels/ms) / ms
const double kMaxSpeedX{0.325};            // pixels / ms
// Fall Motion
const double kMaxSpeedY{0.325};            // pixels / ms
const double kGravity{0.0012};             // (pixels / ms) / ms
// Jump Motion
const double kJumpSpeed{0.325};            // pixels / ms
const auto kJumpTime = std::chrono::milliseconds(275);
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

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b)
{
    return std::tie(a.motion_type, a.horizontal_facing, a.vertical_facing) <
            std::tie(b.motion_type, b.horizontal_facing, b.vertical_facing);
}

Player::Player(Graphics& graphics, Vector<int> pos) :
    pos_(pos),
    velocity_{0.0, 0.0},
    acceleration_{0.0, 0.0},
    horizontal_facing_{HorizontalFacing::LEFT},
    vertical_facing_{VerticalFacing::HORIZONTAL},
    is_on_ground_{false},
    jump_(),
    sprites_()
{
    initializeSprites(graphics);
}

Player::~Player()
{
    ;
}

void Player::update(std::chrono::milliseconds elapsed_time)
{
    sprites_[getSpriteState()]->update(elapsed_time);
    jump_.update(elapsed_time);

    pos_.x += round(velocity_.x * elapsed_time.count());
    velocity_.x += acceleration_.x * elapsed_time.count();
    if (acceleration_.x < 0.0) {
        velocity_.x = std::max(velocity_.x, -kMaxSpeedX);
    } else if (acceleration_.x > 0.0) {
        velocity_.x = std::min(velocity_.x, kMaxSpeedX);
    } else if (is_on_ground_) {
        velocity_.x *= kSlowdownFactor;
    }

    pos_.y += round(velocity_.y * elapsed_time.count());
    if (!jump_.is_active()) {
        velocity_.y += std::min(kGravity * elapsed_time.count(), kMaxSpeedY);
    }

    // FIXME: implement correct collision instead of code below
    if (pos_.y >= 320) {
        pos_.y = 320;
        velocity_.y = 0.0;
    }
    is_on_ground_ = pos_.y == 320;
}

void Player::draw(Graphics& graphics)
{
    sprites_[getSpriteState()]->draw(graphics, pos_);
}

void Player::startMovingLeft()
{
    horizontal_facing_ = HorizontalFacing::LEFT;
    acceleration_.x = -kWalkingAcceleration;
}

void Player::startMovingRight()
{
    horizontal_facing_ = HorizontalFacing::RIGHT;
    acceleration_.x = kWalkingAcceleration;
}

void Player::stopMoving()
{
    acceleration_.x = 0.0;
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
    if (is_on_ground()) {
        jump_.reset();
        velocity_.y = -kJumpSpeed;
    } else if (velocity_.y < 0.0) {
        jump_.reactivate();
    }
}

void Player::stopJump()
{
    jump_.deactivate();
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
        motion = acceleration_.x == 0.0
            ? MotionType::STANDING
            : MotionType::WALKING;
    } else {
        motion = velocity_.y < 0.0
            ? MotionType::JUMPING
            : MotionType::FALLING;
    }
    return SpriteState(motion, horizontal_facing_, vertical_facing_);
}

void Player::Jump::reset()
{
    time_remaining_ = kJumpTime;
    reactivate();
}

void Player::Jump::update(std::chrono::milliseconds elapsed_time)
{
    if (Player::Jump::active_) {
        time_remaining_ -= elapsed_time;
        if (time_remaining_.count() <= 0) {
            Player::Jump::active_ = false;
        }
    }
}
