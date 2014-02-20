#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "graphics.h"
#include "game.h"

Graphics::Graphics() :
    sdlWindow {SDL_CreateWindow(
                "Cave Reconstructed",
                0, 0,
                units::tileToPixel(Game::kScreenWidth),
                units::tileToPixel(Game::kScreenHeight),
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

/**
 * Loads SDL_Texture from file_path into sprite cache (sprite_sheets_ map) and
 * returns it. If texture already presents in cache just returns it.
 */
SDL_Texture* Graphics::loadImage(const std::string& file_path,
        const bool black_is_transparent)
{
    // spritesheet not loaded
    if (sprite_sheets_.count(file_path) == 0) {
        SDL_Texture *t;
        if (black_is_transparent) {
            SDL_Surface *surface = SDL_LoadBMP(file_path.c_str());
            if (surface == nullptr) {
                throw std::runtime_error("Cannot load texture!");
            }
            const Uint32 black_color = SDL_MapRGB(surface->format, 0, 0, 0);
            SDL_SetColorKey(surface, SDL_TRUE, black_color);
            t = SDL_CreateTextureFromSurface(sdlRenderer, surface);
            SDL_FreeSurface(surface);
        } else {
            t = IMG_LoadTexture(sdlRenderer, file_path.c_str());
        }
        if (t == nullptr) {
            throw std::runtime_error("Cannot load texture!");
        }
        sprite_sheets_[file_path] = t;
    }
    return sprite_sheets_[file_path];
}

void Graphics::renderTexture(
        SDL_Texture *tex,
        const SDL_Rect dst,
        const SDL_Rect *clip) const
{
    SDL_RenderCopy(sdlRenderer, tex, clip, &dst);
}

/**
 * Draw an SDL_Texture at some destination rect taking a clip of the
 * texture if desired
 */
void Graphics::renderTexture(
        SDL_Texture *tex,
        const int x,
        const int y,
        const SDL_Rect *clip) const
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != nullptr) {
        dst.w = clip->w;
        dst.h = clip->h;
    } else {
        SDL_QueryTexture(tex, nullptr, nullptr, &dst.w, &dst.h);
    }
    renderTexture(tex, dst, clip);
}

void Graphics::flip() const
{
    SDL_RenderPresent(sdlRenderer);
}

void Graphics::clear() const
{
    SDL_RenderClear(sdlRenderer);
}
