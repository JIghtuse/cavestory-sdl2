#include "backdrop.h"
#include "game.h"

const int kBackgroundSize{Game::kTileSize * 4}; // pixels

FixedBackdrop::FixedBackdrop(const std::string& path, Graphics& graphics) :
    texture_id_{graphics.loadImage(path)}
{
}

void FixedBackdrop::draw(Graphics& graphics) const
{
    for (int x = 0; x < Game::kScreenWidth; x += kBackgroundSize) {
        for (int y = 0; y < Game::kScreenHeight; y += kBackgroundSize) {
            SDL_Rect destination_rectangle{x, y,
                kBackgroundSize, kBackgroundSize};
            graphics.renderTexture(texture_id_, destination_rectangle);
        }
    }
}
