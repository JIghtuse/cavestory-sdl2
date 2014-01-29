#include "map.h"
#include "game.h"
#include "graphics.h"
#include "sprite.h"
#include "vector.h"

const std::string kMapSpriteFilePath{"content/PrtCave.bmp"};

Map::Map() :
    tiles_()
{}

Map::~Map() {}

Map* Map::createTestMap(Graphics& graphics)
{
    using std::vector;
    Map* map = new Map();

    const int num_rows{15}; // 15 * 32 == 480
    const int num_cols{20}; // 20 * 32 == 640
    // Ensure tiles_ is num_rows x num_cols in size
    map->tiles_ = vector<vector<Tile> >(
            num_rows, vector<Tile>(num_cols, Tile()));

    std::shared_ptr<Sprite> sprite{new Sprite(
            graphics,
            kMapSpriteFilePath,
            Game::kTileSize, 0,
            Game::kTileSize, Game::kTileSize
            )};
    Tile tile(TileType::WALL, sprite);
    const int floor_row_idx{11};
    for (auto col = 0; col < num_cols; ++col) {
        map->tiles_[floor_row_idx][col] = tile;
    }
    map->tiles_[10][5] = tile;
    map->tiles_[9][4] = tile;
    map->tiles_[8][3] = tile;
    map->tiles_[7][2] = tile;
    map->tiles_[10][3] = tile;

    return map;
}

void Map::update(std::chrono::milliseconds elapsed_time)
{
    for (auto &row : tiles_) {
        for (auto &col: row) {
            if (col.sprite != nullptr) {
                col.sprite->update(elapsed_time);
            }
        }
    }
}

void Map::draw(Graphics& graphics) const
{
    for (auto row = 0u; row < tiles_.size(); ++row) {
        for (auto col = 0u; col < tiles_[row].size(); ++col) {
            if (tiles_[row][col].sprite != nullptr) {
                Vector<int> pos{
                    static_cast<int>(col) * Game::kTileSize,
                    static_cast<int>(row) * Game::kTileSize
                };

                tiles_[row][col].sprite->draw(graphics, pos);
            }
        }
    }
}
