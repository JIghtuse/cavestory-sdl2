#include <string>
#include "number_sprite.h"
#include "sprite.h"

const std::string kNumberSpritePath{"content/TextBox.bmp"};
const units::Game kSpriteY{7 * units::kHalfTile};
const units::Game kSpriteHeight{units::kHalfTile};
const units::Game kSpriteWidth{units::kHalfTile};

NumberSprite::NumberSprite(Graphics& graphics, int number) :
    sprite_{new Sprite(
            graphics,
            kNumberSpritePath,
            units::gameToPixel(number * units::kHalfTile),
            units::gameToPixel(kSpriteY),
            units::gameToPixel(kSpriteWidth),
            units::gameToPixel(kSpriteHeight)
            )}
{
}

NumberSprite::~NumberSprite() {}

void NumberSprite::draw(Graphics& graphics, Vector<units::Game> pos)
{
    sprite_->draw(graphics, pos);
}
