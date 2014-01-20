#include "game.h"
#include <SDL2/SDL.h>

namespace {
    const int kScreenWidth = 640;
    const int kScreenHeight = 480;
    const double kFps = 60.0;
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
        using std::chrono::high_resolution_clock;
        using std::chrono::milliseconds;

        const auto start_time = high_resolution_clock::now();

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

        const auto end_time = high_resolution_clock::now();

        std::chrono::duration<double> elapsed_time =
            std::chrono::duration_cast<milliseconds>(end_time - start_time);

        auto delay_duration = milliseconds(1000) / kFps - elapsed_time;
        if (delay_duration.count() < 0)
            delay_duration = milliseconds(0);

        SDL_Delay(delay_duration.count());
    }
}

void Game::update()
{
}

void Game::draw()
{
}
