#include "sprite.h"
#include "graphics.h"
#include "sprite.h"

Sprite::Sprite(Graphics& graphics,
        const std::string& file_name,
        const units::Pixel source_x, const units::Pixel source_y,
        const units::Pixel width, const units::Pixel height) :
    texture_{graphics.loadImage(file_name.c_str(), true)},
    source_rect_{source_x, source_y, width, height}
{
}

Sprite::~Sprite()
{
}

void Sprite::draw(Graphics& graphics, const Vector<units::Game>& pos) const
{
    const units::Pixel dstx = units::gameToPixel(pos.x);
    const units::Pixel dsty = units::gameToPixel(pos.y);

    graphics.renderTexture(texture_, dstx, dsty, &source_rect_);
}
