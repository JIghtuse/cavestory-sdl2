#include "game.h"
#include <SDL2/SDL.h>

namespace {
    const int kScreenWidth = 640;
    const int kScreenHeight = 480;
    const int kFps = 60;
}

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(SDL_DISABLE);
    SDL_CreateWindow(
            "Cave",
            0,0,kScreenWidth,kScreenHeight,
            SDL_WINDOW_FULLSCREEN_DESKTOP
            );
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
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_q) {
                    running = false;
                }
                break;
            default:
                break;
            }
        }

        update();
        draw();
        const unsigned int elapsed_time_ms{SDL_GetTicks() - start_time_ms};
        SDL_Delay(1000 / kFps - elapsed_time_ms);
    }
}

void Game::update()
{
}

void Game::draw()
{
}
