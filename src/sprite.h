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
            const std::string& file_name,
            const units::Pixel source_x, const units::Pixel source_y,
            const units::Pixel width, const units::Pixel height
            );
    virtual ~Sprite();

    Sprite(const Sprite&)=delete;
    Sprite& operator=(const Sprite&)=delete;

    virtual void update() {}
    void draw(Graphics& graphics, const Vector<units::Game>& pos) const;

private:
    SDL_Texture *texture_;

protected:
    SDL_Rect source_rect_;
};

#endif /* SPRITE_H */
