#include "varying_width_sprite.h"

VaryingWidthSprite::VaryingWidthSprite(Graphics& graphics,
        const std::string& file_name,
        const units::Pixel source_x, const units::Pixel source_y,
        const units::Pixel width, const units::Pixel height) : 
    Sprite(graphics, file_name, source_x, source_y, width, height)
{}

VaryingWidthSprite::~VaryingWidthSprite() {}

void VaryingWidthSprite::set_width(units::Pixel width)
{
    source_rect_.w = width;
}
