#include <cmath>

#include "player.h"
#include "animated_sprite.h"
#include "graphics.h"
#include "game.h"

const double kSlowdownFactor = 0.8;
const double kWalkingAcceleration = 0.0012; // (pixels/ms) / ms
const double kMaxSpeedX = 0.325;            // pixels / ms

Player::Player(int x, int y, Graphics& graphics) :
    x_{x},
    y_{y},
    sprite_{new AnimatedSprite(
                "content/MyChar.bmp",
                0, 0,
                Game::kTileSize, Game::kTileSize,
                graphics.getRenderer(),
                15, 3
                )},
    velocity_x_{0.0},
    acceleration_x_{0.0}
{
    ;
}

Player::~Player()
{
    ;
}

void Player::update(std::chrono::duration<double,std::milli> elapsed_time)
{
    sprite_->update(elapsed_time);
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
    sprite_->draw(graphics, x_, y_);
}

void Player::startMovingLeft()
{
    acceleration_x_ = -kWalkingAcceleration;
}

void Player::startMovingRight()
{
    acceleration_x_ = kWalkingAcceleration;
}

void Player::stopMoving()
{
    acceleration_x_ = 0.0;
}
