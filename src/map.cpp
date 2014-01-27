#include "map.h"
#include "game.h"
#include "graphics.h"
#include "sprite.h"
#include "vector.h"

Map::Map() :
    foreground_sprites_()
{}

Map::~Map() {}

void Map::update(std::chrono::milliseconds elapsed_time)
{
    for (auto &row : foreground_sprites_) {
        for (auto &col: row) {
            if (col != nullptr) {
                col->update(elapsed_time);
            }
        }
    }
}

void Map::draw(Graphics& graphics) const
{
    for (auto row = 0u; row < foreground_sprites_.size(); ++row) {
        for (auto col = 0u; col < foreground_sprites_.size(); ++col) {
            if (foreground_sprites_[row][col] != nullptr) {
                Vector<int> pos{
                    static_cast<int>(col) * Game::kTileSize,
                    static_cast<int>(row) * Game::kTileSize
                };

                foreground_sprites_[row][col]->draw(graphics, pos);
            }
        }
    }
}
