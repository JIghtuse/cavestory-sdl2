#include <cmath>

#include "player.h"
#include "animated_sprite.h"
#include "graphics.h"
#include "game.h"

const double kSlowdownFactor = 0.8;
const double kWalkingAcceleration = 0.0012; // (pixels/ms) / ms
const double kMaxSpeedX = 0.325;            // pixels / ms

bool operator<(const Player::SpriteState& a, const Player::SpriteState& b)
{
    return std::tie(a.motion_type, a.horizontal_facing) <
            std::tie(b.motion_type, b.horizontal_facing);
}

Player::Player(Graphics& graphics, int x, int y) :
    x_{x},
    y_{y},
    velocity_x_{0.0},
    acceleration_x_{0.0},
    horizontal_facing_(HorizontalFacing::LEFT),
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
    x_ += round(velocity_x_ * elapsed_time.count());
    velocity_x_ += acceleration_x_ * elapsed_time.count();
    if (acceleration_x_ < 0.0) {
        velocity_x_ = std::max(velocity_x_, -kMaxSpeedX);
    } else if (acceleration_x_ > 0.0) {
        velocity_x_ = std::min(velocity_x_, kMaxSpeedX);
    } else {
        velocity_x_ *= kSlowdownFactor;
    }
}

void Player::draw(Graphics& graphics)
{
    sprites_[getSpriteState()]->draw(graphics, x_, y_);
}

void Player::startMovingLeft()
{
    horizontal_facing_ = HorizontalFacing::LEFT;
    acceleration_x_ = -kWalkingAcceleration;
}

void Player::startMovingRight()
{
    horizontal_facing_ = HorizontalFacing::RIGHT;
    acceleration_x_ = kWalkingAcceleration;
}

void Player::stopMoving()
{
    acceleration_x_ = 0.0;
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
            acceleration_x_ == 0.0 ? MotionType::STANDING
                                   : MotionType::WALKING,
            horizontal_facing_);
}
