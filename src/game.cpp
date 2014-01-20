#include "game.h"
#include <SDL2/SDL.h>

Game::Game() :
    fpsDelay(60)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    runEventLoop();
}

Game::~Game()
{
    SDL_Quit();
}

void Game::runEventLoop() {
    bool running{true};
    while (running) {
        SDL_Delay(1000 / fpsDelay);
    }
    // TODO
    // while (running) - 60 Hz
    // Handle input. Handle timer callbacks.
    // update(). Move the player. Move projectiles. Check collisions
    // draw()    draw everything!
}
