#include "backdrop.h"
#include "game.h"
#include "units.h"

const units::Tile kBackgroundSize{4};

FixedBackdrop::FixedBackdrop(const std::string& path, Graphics& graphics) :
    texture_id_{graphics.loadImage(path)}
{
}

void FixedBackdrop::draw(Graphics& graphics) const
{
    for (units::Tile x = 0; x < Game::kScreenWidth; x += kBackgroundSize) {
        for (units::Tile y = 0; y < Game::kScreenHeight; y += kBackgroundSize) {
            SDL_Rect destination_rectangle{
                units::tileToPixel(x), units::tileToPixel(y),
                kBackgroundSize, kBackgroundSize
            };
            graphics.renderTexture(texture_id_, destination_rectangle);
        }
    }
}
