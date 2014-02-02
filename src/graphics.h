#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

struct Graphics
{
    Graphics();
    ~Graphics();

    Graphics(const Graphics&)=delete;
    Graphics& operator=(const Graphics&)=delete;

    SDL_Texture* loadImage(const std::string& file_path,
            bool black_is_transparent=false);

    void renderTexture(SDL_Texture *tex, SDL_Rect dst, SDL_Rect *clip=nullptr);
    void renderTexture(SDL_Texture *tex, int x, int y, SDL_Rect *clip=nullptr);

    void flip();
    void clear();

private:
    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
    std::map<std::string, SDL_Texture*> sprite_sheets_;
};

#endif /*  GRAPHICS_H  */
