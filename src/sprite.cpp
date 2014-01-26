#include "sprite.h"
#include "graphics.h"
#include "sprite.h"

Sprite::Sprite(Graphics& graphics,
        const std::string& file_path,
        int source_x, int source_y,
        int width, int height) :
    texture_{graphics.loadImage(file_path.c_str())},
    source_rect_{source_x, source_y, width, height}
{
}

Sprite::~Sprite()
{
    //SDL_DestroyTexture(texture_);
}

void Sprite::draw(Graphics& graphics, int x, int y)
{
    graphics.renderTexture(texture_, x, y, &source_rect_);
}
