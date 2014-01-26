#include <cmath>

#include "player.h"
#include "animated_sprite.h"
#include "graphics.h"
#include "game.h"

const double kSlowdownFactor = 0.8;
const double kWalkingAcceleration = 0.0012; // (pixels/ms) / ms
const double kMaxSpeedX = 0.325;            // pixels / ms
const double kMaxSpeedY = 0.325;            // pixels / ms
const double kGravity = 0.0012;             // (pixels / ms) / ms
const double kJumpSpeed = 0.325;            // pixels / ms
const auto kJumpTime = std::chrono::milliseconds(275);

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b)
{
    return std::tie(a.motion_type, a.horizontal_facing) <
            std::tie(b.motion_type, b.horizontal_facing);
}

Player::Player(Graphics& graphics, Vector<int> pos) :
    pos_(pos),
    velocity_{0.0, 0.0},
    acceleration_{0.0, 0.0},
    horizontal_facing_{HorizontalFacing::LEFT},
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

void Player::initializeSprites(Graphics& graphics)
{
    sprites_[SpriteState(MotionType::STANDING, HorizontalFacing::LEFT)] =
        std::unique_ptr<Sprite>{new Sprite(
                graphics,
                "content/MyChar.bmp",
                0, 0, Game::kTileSize, Game::kTileSize)};
    sprites_[SpriteState(MotionType::WALKING, HorizontalFacing::LEFT)] =
        std::unique_ptr<Sprite>{new AnimatedSprite(
                graphics,
                "content/MyChar.bmp",
                0, 0, Game::kTileSize, Game::kTileSize,
                15, 3)};
    sprites_[SpriteState(MotionType::STANDING, HorizontalFacing::RIGHT)] =
        std::unique_ptr<Sprite>{new Sprite(
                graphics,
                "content/MyChar.bmp",
                0, Game::kTileSize, Game::kTileSize, Game::kTileSize)};
    sprites_[SpriteState(MotionType::WALKING, HorizontalFacing::RIGHT)] =
        std::unique_ptr<Sprite>{new AnimatedSprite(
                graphics,
                "content/MyChar.bmp",
                0, Game::kTileSize, Game::kTileSize, Game::kTileSize,
                15, 3)};
}

Player::SpriteState Player::getSpriteState()
{
    return SpriteState(
            acceleration_.x == 0.0 ? MotionType::STANDING
                                   : MotionType::WALKING,
            horizontal_facing_);
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
