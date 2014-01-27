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
   std::vector<std::vector<std::shared_ptr<Sprite> > >foreground_sprites_;
};

#endif /* MAP_H_ */
