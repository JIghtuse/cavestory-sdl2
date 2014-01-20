#ifndef GRAPHICS_H
#define GRAPHICS_H

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;

struct Graphics
{
    Graphics();
    ~Graphics();

    Graphics(const Graphics&)=delete;
    Graphics operator=(const Graphics&)=delete;

    void renderTexture(SDL_Texture *texture);

private:
    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
};

#endif /*  GRAPHICS_H  */
