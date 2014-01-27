#include "map.h"
#include "game.h"
#include "graphics.h"
#include "sprite.h"
#include "vector.h"

const std::string kMapSpriteFilePath{"content/PrtCave.bmp"};

Map::Map() :
    foreground_sprites_()
{}

Map::~Map() {}

Map* Map::createTestMap(Graphics& graphics)
{
    using std::vector;
    Map* map = new Map();

    const int num_rows{15}; // 15 * 32 == 480
    const int num_cols{20}; // 20 * 32 == 640
    // Ensure foreground_sprites_ is num_rows x num_cols in size
    map->foreground_sprites_ = vector<vector<std::shared_ptr<Sprite> > >(
            num_rows, vector<std::shared_ptr<Sprite> >(
                num_cols, std::shared_ptr<Sprite>()));

    std::shared_ptr<Sprite> sprite{new Sprite(
            graphics,
            kMapSpriteFilePath,
            Game::kTileSize, 0,
            Game::kTileSize, Game::kTileSize
            )};
    const int floor_row_idx{11};
    for (auto col = 0; col < num_cols; ++col) {
        map->foreground_sprites_[floor_row_idx][col] = sprite;
    }
    map->foreground_sprites_[10][5] = sprite;

    return map;
}

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
