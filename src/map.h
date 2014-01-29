#ifndef MAP_H_
#define MAP_H_

#include <chrono>
#include <memory>
#include <vector>

struct Graphics;
struct Sprite;

struct Map {
   Map();
   ~Map();

   static Map* createTestMap(Graphics& graphics);

   void update(std::chrono::milliseconds elapsed_time);
   void draw(Graphics& graphics) const;
private:
   enum class TileType {
       AIR,
       WALL
   };
   struct Tile {
       Tile(TileType tile_type=TileType::AIR,
               std::shared_ptr<Sprite> sprite=std::shared_ptr<Sprite>()) :
           tile_type(tile_type),
           sprite(sprite)
       {}

       TileType tile_type;
       std::shared_ptr<Sprite> sprite;
   };
   std::vector<std::vector<Tile> >tiles_;
};

#endif /* MAP_H_ */
