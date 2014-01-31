#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <stdexcept>

struct SDLEngine
{
    SDLEngine()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error("SDL_Init");
        }
        if (SDL_ShowCursor(SDL_DISABLE) < 0) {
            throw std::runtime_error("SDL_ShowCursor");
        }
    }
    ~SDLEngine()
    {
        SDL_Quit();
    }
};

#endif /* SDL_H */
