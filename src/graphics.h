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

    SDL_Texture* loadImage(const std::string& file_name,
            const bool black_is_transparent=false);

    void renderTexture(SDL_Texture *tex,
            const SDL_Rect dst,
            const SDL_Rect *clip=nullptr) const;
    void renderTexture(SDL_Texture *tex,
            const int x, const int y,
            const SDL_Rect *clip=nullptr) const;

    void flip() const;
    void clear() const;

private:
    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
    std::map<std::string, SDL_Texture*> sprite_sheets_;
};

#endif /*  GRAPHICS_H  */
