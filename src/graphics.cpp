#include "graphics.h"
#include <SDL2/SDL.h>

const int kScreenWidth = 640;
const int kScreenHeight = 480;

Graphics::Graphics() :
    sdlWindow (
            SDL_CreateWindow(
                "Cave Reconstructed",
                0, 0, kScreenWidth,kScreenHeight,
                SDL_WINDOW_FULLSCREEN_DESKTOP
                )
            ),
    sdlRenderer (
            SDL_CreateRenderer(sdlWindow, -1, 0)
            )
{
}

Graphics::~Graphics()
{
}

void Graphics::renderTexture(SDL_Texture *texture)
{
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, texture, NULL, NULL);
    SDL_RenderPresent(sdlRenderer);
}
