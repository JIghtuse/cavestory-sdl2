#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>

class SDLEngine
{
    SDLEngine()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_ShowCursor(SDL_DISABLE);
    }
    ~SDLEngine()
    {
        SDL_Quit();
    }
};

#endif /* SDL_H */
