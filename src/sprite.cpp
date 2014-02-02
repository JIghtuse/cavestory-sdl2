#include "sprite.h"
#include "graphics.h"
#include "sprite.h"

Sprite::Sprite(Graphics& graphics,
        const std::string& file_path,
        int source_x, int source_y,
        int width, int height) :
    texture_{graphics.loadImage(file_path.c_str(), true)},
    source_rect_{source_x, source_y, width, height}
{
}

Sprite::~Sprite()
{
}

void Sprite::draw(Graphics& graphics, Vector<int>& pos)
{
    graphics.renderTexture(texture_, pos.x, pos.y, &source_rect_);
}
