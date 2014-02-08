#ifndef SPRITE_H
#define SPRITE_H

#include <chrono>
#include <string>
#include <SDL2/SDL.h>
#include "vector.h"
#include "units.h"

struct Graphics;

struct Sprite {
    Sprite(
            Graphics& graphics,
            const std::string& file_path,
            units::Pixel source_x, units::Pixel source_y,
            units::Pixel width, units::Pixel height
            );
    virtual ~Sprite();

    Sprite(const Sprite&)=delete;
    Sprite& operator=(const Sprite&)=delete;

    virtual void update(std::chrono::milliseconds) {}
    void draw(Graphics& graphics, Vector<units::Game>& pos);

private:
    SDL_Texture *texture_;

protected:
    SDL_Rect source_rect_;
};

#endif /* SPRITE_H */
