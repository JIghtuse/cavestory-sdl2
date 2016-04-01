#ifndef MAP_H_
#define MAP_H_

#include <chrono>
#include <memory>
#include <vector>
#include "backdrop.h"
#include "units.h"

struct Graphics;
struct Sprite;
struct Rectangle;

struct Map {
   Map();
   ~Map();

   enum class TileType {
       AIR,
       WALL
   };

   struct CollisionTile {
       CollisionTile(units::Tile row, units::Tile col, TileType tile_type) :
           row(row),
           col(col),
           tile_type(tile_type)
       {}
       units::Tile row;
       units::Tile col;
       TileType tile_type;
   };

   static std::unique_ptr<Map> createTestMap(Graphics& graphics);

   const std::vector<CollisionTile>
       getCollidingTiles(const Rectangle& rect) const;

   void drawBackground(Graphics& graphics) const;
   void draw(Graphics& graphics) const;
private:
   struct Tile {
       Tile(TileType tile_type=TileType::AIR,
               std::shared_ptr<Sprite> sprite=std::shared_ptr<Sprite>()) :
           tile_type(tile_type),
           sprite(sprite)
       {}

       TileType tile_type;
       std::shared_ptr<Sprite> sprite;
   };
   std::unique_ptr<Backdrop> backdrop_;
   std::vector<std::vector<std::shared_ptr<Sprite> > > background_tiles_;
   std::vector<std::vector<Tile> >tiles_;
};

#endif /* MAP_H_ */
