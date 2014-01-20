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
    SDL_Event event;

    bool running{true};
    while (running) {
        const unsigned int start_time_ms{SDL_GetTicks()};
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            default:
                break;
            }
        }

        update();
        draw();
        const unsigned int elapsed_time_ms{SDL_GetTicks() - start_time_ms};
        SDL_Delay(1000 / fpsDelay - elapsed_time_ms);
    }
    // TODO
    // while (running) - 60 Hz
    // Handle input. Handle timer callbacks.
    // update(). Move the player. Move projectiles. Check collisions
    // draw()    draw everything!
}

void Game::update()
{
}

void Game::draw()
{
}
