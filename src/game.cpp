#include "game.h"
#include "input.h"
#include "player.h"

const double kFps = 60.0;

int Game::kTileSize = 32;

Game::Game() :
    sdlEngine_(),
    graphics_(),
    player_{new Player(320, 240, graphics_)}
{
    runEventLoop();
}

Game::~Game()
{
}

void Game::runEventLoop() {
    Input input;
    SDL_Event event;

    bool running{true};
    auto last_updated_time = std::chrono::high_resolution_clock::now();
    while (running) {
        using std::chrono::high_resolution_clock;
        using std::chrono::milliseconds;
        using std::chrono::duration_cast;
        using std::chrono::duration;

        const auto start_time = high_resolution_clock::now();

        input.beginNewFrame();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                input.keyDownEvent(event);
                break;
            case SDL_KEYUP:
                input.keyUpEvent(event);
                break;
            default:
                break;
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_Q)) {
            running = false;
        }

        if (input.isKeyHeld(SDL_SCANCODE_LEFT)
                && input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
            // if both left and right are being pressed we need to stop moving
            player_->stopMoving();
        } else if (input.isKeyHeld(SDL_SCANCODE_LEFT)) {
            player_->startMovingLeft();
        } else if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
            player_->startMovingRight();
        } else {
            player_->stopMoving();
        }

        // update scene and last_updated_time
        const auto current_time = high_resolution_clock::now();
        update(duration_cast<milliseconds>(current_time - last_updated_time));
        last_updated_time = current_time;

        draw(graphics_);

        // calculate delay for constant fps
        const auto end_time = high_resolution_clock::now();
        duration<double,std::milli> elapsed_time = (end_time - start_time);

        auto delay_duration = milliseconds(1000) / kFps - elapsed_time;
        if (delay_duration.count() < 0)
            delay_duration = milliseconds(0);

        SDL_Delay(delay_duration.count());
    }
}

void Game::update(std::chrono::duration<double,std::milli> elapsed_time)
{
    player_->update(elapsed_time);
}

void Game::draw(Graphics& graphics)
{
    player_->draw(graphics);
    graphics.flip();
}
