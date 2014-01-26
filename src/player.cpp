#include <cmath>

#include "player.h"
#include "animated_sprite.h"
#include "graphics.h"
#include "game.h"

const double kSlowdownFactor = 0.8;
const double kWalkingAcceleration = 0.0012; // (pixels/ms) / ms
const double kMaxSpeedX = 0.325;            // pixels / ms
//const double kJumpSpeed = 0.325;            // pixels / ms

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
    sprites_()
{
    initializeSprites(graphics);
}

Player::~Player()
{
    ;
}

void Player::update(std::chrono::duration<double,std::milli> elapsed_time)
{
    sprites_[getSpriteState()]->update(elapsed_time);
    pos_.x += round(velocity_.x * elapsed_time.count());
    velocity_.x += acceleration_.x * elapsed_time.count();
    if (acceleration_.x < 0.0) {
        velocity_.x = std::max(velocity_.x, -kMaxSpeedX);
    } else if (acceleration_.x > 0.0) {
        velocity_.x = std::min(velocity_.x, kMaxSpeedX);
    } else {
        velocity_.x *= kSlowdownFactor;
    }
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
    //if (is_on_ground()) {
        //jump_.reset();
        //velocity_.y = -kJumpSpeed;
    //} else if (velocity_.y < 0.0) {
        //jump_.reactivate();
    //}
}

void Player::stopJump()
{
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
