#include "game.h"
#include "sdlengine.h"
#include "graphics.h"

const double kFps = 60.0;

Game::Game()
{
    runEventLoop();
}

Game::~Game()
{
}

void Game::runEventLoop() {
    SDLEngine sdlEngine;
    Graphics graphics;

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
