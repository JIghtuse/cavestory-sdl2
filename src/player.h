#ifndef PLAYER_H_
#define PLAYER_H_

#include <chrono>
#include <memory>
#include "sprite.h"

struct Graphics;

struct Player {
   Player(int x, int y, Graphics& graphics);
   ~Player();

   void update(std::chrono::duration<double,std::milli> elapsed_time);
   void draw(Graphics& graphics);

private:
   int x_;
   int y_;
   std::unique_ptr<Sprite> sprite_;
   static int kTileSize;
};

#endif /* SRC/PLAYER_H_ */
