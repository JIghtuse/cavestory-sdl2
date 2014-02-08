#include "sprite.h"
#include "graphics.h"
#include "sprite.h"

Sprite::Sprite(Graphics& graphics,
        const std::string& file_path,
        units::Pixel source_x, units::Pixel source_y,
        units::Pixel width, units::Pixel height) :
    texture_{graphics.loadImage(file_path.c_str(), true)},
    source_rect_{source_x, source_y, width, height}
{
}

Sprite::~Sprite()
{
}

void Sprite::draw(Graphics& graphics, Vector<units::Game>& pos)
{
    units::Pixel dstx = units::gameToPixel(pos.x);
    units::Pixel dsty = units::gameToPixel(pos.y);

    graphics.renderTexture(texture_, dstx, dsty, &source_rect_);
}
