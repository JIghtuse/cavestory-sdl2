#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <memory>
#include "sdlengine.h"
#include "graphics.h"

struct Sprite;

struct Game {
    Game();
    ~Game();
private:
    void runEventLoop();
    void update();
    void draw(Graphics& graphics);

    SDLEngine sdlEngine_;
    Graphics graphics_;
    std::unique_ptr<Sprite> sprite_;
};

#endif /* GAME_H */
