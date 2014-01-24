#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

struct Graphics
{
    Graphics();
    ~Graphics();

    Graphics(const Graphics&)=delete;
    Graphics& operator=(const Graphics&)=delete;

    void renderTexture(
            SDL_Texture *tex,
            SDL_Renderer *ren,
            SDL_Rect dst,
            SDL_Rect *clip=nullptr);
    void renderTexture(
            SDL_Texture *tex,
            SDL_Renderer *ren,
            int x,
            int y,
            SDL_Rect *clip=nullptr);

    void flip();

    SDL_Renderer *getRenderer()
    {
        return sdlRenderer;
    }

private:
    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
};

#endif /*  GRAPHICS_H  */
