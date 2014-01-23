#include "game.h"
#include "input.h"
#include "animated_sprite.h"

const double kFps = 60.0;

int Game::kTileSize = 32;

Game::Game() :
    sdlEngine_(),
    graphics_(),
    sprite_{new AnimatedSprite(
            "content/MyChar.bmp",
            0, 0,
            kTileSize, kTileSize,
            graphics_.getRenderer(),
            15, 3
            )}
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
                if (event.key.keysym.sym == SDLK_q) {
                    running = false;
                }
                break;
            case SDL_KEYUP:
                input.keyDownEvent(event);
                break;
            default:
                break;
            }
        }
        if (input.wasKeyPressed(SDL_SCANCODE_Q)) {
            running = false;
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
    sprite_->update(elapsed_time);
}

void Game::draw(Graphics& graphics)
{
    sprite_->draw(graphics, 320, 240);
    graphics.flip();
}
