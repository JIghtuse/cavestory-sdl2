#ifndef SPRITE_H
#define SPRITE_H

#include <chrono>
#include <string>
#include <SDL2/SDL.h>

struct Graphics;

struct Sprite {
    Sprite(
            Graphics& graphics,
            const std::string& file_path,
            int source_x, int source_y,
            int width, int height
            );
    virtual ~Sprite();

    Sprite(const Sprite&)=delete;
    Sprite& operator=(const Sprite&)=delete;

    virtual void update(std::chrono::duration<double,std::milli>) {};
    void draw(Graphics& graphics, int x, int y);

private:
    SDL_Texture *texture_;

protected:
    SDL_Rect source_rect_;
};

#endif /* SPRITE_H */
