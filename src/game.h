#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <memory>
#include "sdlengine.h"
#include "graphics.h"

struct Player;

struct Game {
    Game();
    ~Game();

    static int kTileSize;
private:
    void runEventLoop();
    void update(std::chrono::duration<double,std::milli> elapsed_time);
    void draw(Graphics& graphics);

    SDLEngine sdlEngine_;
    Graphics graphics_;
    std::unique_ptr<Player> player_;
};

#endif /* GAME_H */
