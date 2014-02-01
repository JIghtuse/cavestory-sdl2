#include "backdrop.h"

const int kBackgroundSize{128}; // pixels

FixedBackdrop::FixedBackdrop(const std::string& path, Graphics& graphics) :
    texture_id_{graphics.loadImage(path)}
{
}

void FixedBackdrop::draw(Graphics& graphics) const
{
    const int screen_width{640};
    const int screen_height{480};

    for (int x = 0; x < screen_width; x += kBackgroundSize) {
        for (int y = 0; y < screen_height; y += kBackgroundSize) {
            SDL_Rect destination_rectangle{x, y, kBackgroundSize,
                kBackgroundSize};
            graphics.renderTexture(texture_id_, destination_rectangle);
        }
    }
}
