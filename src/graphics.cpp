#include <SDL2/SDL_image.h>
#include <stdexcept>
#include "graphics.h"

const int kScreenWidth = 640;
const int kScreenHeight = 480;

Graphics::Graphics() :
    sdlWindow {SDL_CreateWindow(
                "Cave Reconstructed",
                0, 0, kScreenWidth,kScreenHeight,
                SDL_WINDOW_FULLSCREEN_DESKTOP
                )},
    sdlRenderer {SDL_CreateRenderer(
            sdlWindow,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)},
    sprite_sheets_()
{
    if (sdlWindow == nullptr) {
        throw std::runtime_error("SDL_CreateWindow");
    }
    if (sdlRenderer == nullptr) {
        throw std::runtime_error("SDL_CreateRenderer");
    }
}

Graphics::~Graphics()
{
    for (auto& kv : sprite_sheets_) {
        SDL_DestroyTexture(kv.second);
    }
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
}

SDL_Texture* Graphics::loadImage(const std::string& file_path)
{
    // spritesheet not loaded
    if (sprite_sheets_.count(file_path) == 0) {
        sprite_sheets_[file_path] = IMG_LoadTexture(sdlRenderer,
                file_path.c_str());
    }
    return sprite_sheets_[file_path];
}

void Graphics::renderTexture(
        SDL_Texture *tex,
        SDL_Rect dst,
        SDL_Rect *clip)
{
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, tex, clip, &dst);
}

/**
 * Draw an SDL_Texture at some destination rect taking a clip of the
 * texture if desired
 */
void Graphics::renderTexture(
        SDL_Texture *tex,
        int x,
        int y,
        SDL_Rect *clip)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != nullptr) {
        dst.w = clip->w;
        dst.h = clip->h;
    } else {
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }
    renderTexture(tex, dst, clip);
}

void Graphics::flip()
{
    SDL_RenderPresent(sdlRenderer);
}
