#ifndef GAME_H
#define GAME_H

#include <chrono>
#include <memory>
#include "sdlengine.h"
#include "graphics.h"

struct Map;
struct Player;

struct Game {
    Game();
    ~Game();

    static int kTileSize;
    static int kScreenWidth;
    static int kScreenHeight;
private:
    void runEventLoop();
    void update(std::chrono::milliseconds elapsed_time);
    void draw(Graphics& graphics);

    SDLEngine sdlEngine_;
    Graphics graphics_;
    std::unique_ptr<Player> player_;
    std::unique_ptr<Map> map_;
};

#endif /* GAME_H */
