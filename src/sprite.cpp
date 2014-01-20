#include "sprite.h"
#include "graphics.h"
#include "sprite.h"

Sprite::Sprite(const std::string& file_path,
            int source_x, int source_y,
            int width, int height, SDL_Renderer *renderer) :
    renderer_(renderer),
    surface_{SDL_LoadBMP(file_path.c_str())},
    texture_{SDL_CreateTextureFromSurface(renderer_, surface_)},
    source_rect_{source_x, source_y, width, height}
{
    SDL_FreeSurface(surface_);
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(texture_);
}

void Sprite::draw(Graphics& graphics, int x, int y)
{
    graphics.renderTexture(texture_, graphics.getRenderer(), x, y);
}
