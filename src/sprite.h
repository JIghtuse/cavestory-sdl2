#ifndef SPRITE_H
#define SPRITE_H

#include <chrono>
#include <string>
#include <SDL2/SDL.h>
#include "vector.h"

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

    virtual void update(std::chrono::milliseconds) {}
    void draw(Graphics& graphics, Vector<int>& pos);

private:
    SDL_Texture *texture_;

protected:
    SDL_Rect source_rect_;
};

#endif /* SPRITE_H */
