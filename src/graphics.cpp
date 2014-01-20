#include "graphics.h"
#include <stdexcept>

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
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE)}
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
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
}

void Graphics::renderTexture(
        SDL_Texture *tex,
        SDL_Renderer *ren,
        SDL_Rect dst,
        SDL_Rect *clip)
{
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, clip, &dst);
}

/**
 * Draw an SDL_Texture at some destination rect taking a clip of the
 * texture if desired
 */
void Graphics::renderTexture(
        SDL_Texture *tex,
        SDL_Renderer *ren,
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
    renderTexture(tex, ren, dst, clip);
}

void Graphics::flip()
{
    SDL_RenderPresent(sdlRenderer);
}
