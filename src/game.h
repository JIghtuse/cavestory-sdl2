#ifndef GAME_H
#define GAME_H

#include <chrono>

struct SDL_Window;
struct SDL_Renderer;
class SDLEngine;

struct Game {
    Game();
    ~Game();

    Game(const Game&)=delete;
    Game operator=(const Game&)=delete;
private:
    void runEventLoop();
    void update();
    void draw();

    SDLEngine *sdlEngine;
    SDL_Window *sdlWindow;
    SDL_Renderer *sdlRenderer;
};

#endif /* GAME_H */
