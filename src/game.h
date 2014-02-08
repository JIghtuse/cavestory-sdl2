#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <memory>
#include "sdlengine.h"
#include "graphics.h"
#include "units.h"

struct Map;
struct Player;
struct FirstCaveBat;

struct Game {
    Game();
    ~Game();

    static units::Tile kScreenWidth;
    static units::Tile kScreenHeight;

private:
    void runEventLoop();
    void update(std::chrono::milliseconds elapsed_time);
    void draw(Graphics& graphics);

    SDLEngine sdlEngine_;
    Graphics graphics_;
    std::unique_ptr<Player> player_;
    std::unique_ptr<FirstCaveBat> bat_;
    std::unique_ptr<Map> map_;
};

#endif /* GAME_H */
