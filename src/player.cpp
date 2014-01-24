#include "player.h"
#include "animated_sprite.h"
#include "graphics.h"

int Player::kTileSize = 32;

Player::Player(int x, int y, Graphics& graphics) :
    x_{x},
    y_{y},
    sprite_{new AnimatedSprite(
                "content/MyChar.bmp",
                0, 0,
                kTileSize, kTileSize,
                graphics.getRenderer(),
                15, 3
                )}
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
}

void Player::draw(Graphics& graphics)
{
    sprite_->draw(graphics, x_, y_);
}
