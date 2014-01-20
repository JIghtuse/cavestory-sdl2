#include "game.h"

Game::Game()
{
    runEventLoop();
}

Game::~Game()
{
}

void Game::runEventLoop() {
    bool running{true};
    while (running) {

    }
    // TODO
    // while (running) - 60 Hz
    // Handle input. Handle timer callbacks.
    // update(). Move the player. Move projectiles. Check collisions
    // draw()    draw everything!
}
