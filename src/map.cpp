#include "map.h"
#include "game.h"
#include "graphics.h"
#include "rectangle.h"
#include "sprite.h"
#include "vector.h"

const std::string kMapSpriteFilePath{"content/PrtCave.bmp"};

Map::Map() :
    backdrop_(),
    background_tiles_(),
    tiles_()
{}

Map::~Map() {}

Map* Map::createTestMap(Graphics& graphics)
{
    using std::vector;
    Map* map = new Map();

    const std::string bkPath{"content/bkBlue.bmp"};
    map->backdrop_.reset(new FixedBackdrop(bkPath, graphics));

    const units::Tile num_rows{15}; // 15 * 32 == 480
    const units::Tile num_cols{20}; // 20 * 32 == 640
    // Ensure tiles_ and background_tiles_ is num_rows x num_cols in size
    map->tiles_ = vector<vector<Tile> >(
            num_rows, vector<Tile>(
                num_cols, Tile()));

    map->background_tiles_ = vector<vector<std::shared_ptr<Sprite> > >(
            num_rows, vector<std::shared_ptr<Sprite> >(
                num_cols, std::shared_ptr<Sprite>()));

    std::shared_ptr<Sprite> sprite{new Sprite(
            graphics,
            kMapSpriteFilePath,
            units::tileToPixel(1), units::tileToPixel(0),
            units::tileToPixel(1), units::tileToPixel(1)
            )};
    Tile tile(TileType::WALL, sprite);
    const units::Tile row{11};
    for (units::Tile col = 0; col < num_cols; ++col) {
        map->tiles_[row][col] = tile;
    }
    map->tiles_[10][5] = tile;
    map->tiles_[8][5] = tile;
    map->tiles_[9][4] = tile;
    map->tiles_[8][3] = tile;
    map->tiles_[7][2] = tile;
    map->tiles_[10][3] = tile;

    map->tiles_[10][0] = tile;
    map->tiles_[9][0] = tile;
    map->tiles_[8][0] = tile;
    map->tiles_[7][0] = tile;
    map->tiles_[6][0] = tile;
    map->tiles_[5][0] = tile;
    map->tiles_[4][0] = tile;
    map->tiles_[3][0] = tile;
    map->tiles_[10][19] = tile;
    map->tiles_[9][19] = tile;
    map->tiles_[8][19] = tile;
    map->tiles_[7][19] = tile;

    std::shared_ptr<Sprite> chain_top{new Sprite(
            graphics,
            kMapSpriteFilePath,
            units::tileToPixel(11), units::tileToPixel(2),
            units::tileToPixel(1), units::tileToPixel(1)
            )};
    std::shared_ptr<Sprite> chain_middle{new Sprite(
            graphics,
            kMapSpriteFilePath,
            units::tileToPixel(12), units::tileToPixel(2),
            units::tileToPixel(1), units::tileToPixel(1)
            )};
    std::shared_ptr<Sprite> chain_bottom{new Sprite(
            graphics,
            kMapSpriteFilePath,
            units::tileToPixel(13), units::tileToPixel(2),
            units::tileToPixel(1), units::tileToPixel(1)
            )};

    map->background_tiles_[8][2] = chain_top;
    map->background_tiles_[9][2] = chain_middle;
    map->background_tiles_[10][2] = chain_bottom;

    return map;
}


std::vector<Map::CollisionTile>
Map::getCollidingTiles(const Rectangle& rect) const
{
    const units::Tile first_row = units::gameToTile(rect.getTop());
    const units::Tile last_row = units::gameToTile(rect.getBottom());
    const units::Tile first_col = units::gameToTile(rect.getLeft());
    const units::Tile last_col = units::gameToTile(rect.getRight());
    // TODO: throw exception if we fall off the screen
    std::vector<CollisionTile> collision_tiles;

    for (units::Tile row = first_row; row <= last_row; ++row) {
        for (units::Tile col = first_col; col <= last_col; ++col) {
            collision_tiles.push_back(
                    CollisionTile(row, col, tiles_[row][col].tile_type));
        }
    }

    return collision_tiles;
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

void Map::drawBackground(Graphics& graphics) const
{
    backdrop_->draw(graphics);
    for (auto row = 0u; row < background_tiles_.size(); ++row) {
        for (auto col = 0u; col < background_tiles_[row].size(); ++col) {
            if (background_tiles_[row][col] != nullptr) {
                Vector<units::Game> pos{
                    units::tileToGame(col),
                    units::tileToGame(row)
                };
                background_tiles_[row][col]->draw(graphics, pos);
            }
        }
    }
}

void Map::draw(Graphics& graphics) const
{
    for (auto row = 0u; row < tiles_.size(); ++row) {
        for (auto col = 0u; col < tiles_[row].size(); ++col) {
            if (tiles_[row][col].sprite != nullptr) {
                Vector<units::Game> pos{
                    units::tileToGame(col),
                    units::tileToGame(row)
                };
                tiles_[row][col].sprite->draw(graphics, pos);
            }
        }
    }
}
