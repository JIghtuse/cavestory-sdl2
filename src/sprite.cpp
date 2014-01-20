#include "sprite.h"
#include "graphics.h"
#include "sprite.h"
#include <SDL2/SDL_image.h>

Sprite::Sprite(const std::string& file_path,
            int source_x, int source_y,
            int width, int height, SDL_Renderer* ren) :
    renderer_{ren},
    texture_{IMG_LoadTexture(renderer_, file_path.c_str())},
    source_rect_{source_x, source_y, width, height}
{
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture_);
}

void Sprite::draw(Graphics& graphics, int x, int y)
{
    graphics.renderTexture(texture_, renderer_, x, y, &source_rect_);
}
