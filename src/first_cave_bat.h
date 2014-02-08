#ifndef FIRST_CAVE_BAT_H_
#define FIRST_CAVE_BAT_H_

#include <memory>
#include <chrono>
#include "vector.h"
#include "units.h"

struct Sprite;
struct Graphics;

struct FirstCaveBat {
   FirstCaveBat(Graphics& graphics, Vector<units::Game> pos);
   ~FirstCaveBat();

   void draw(Graphics& graphics);
   void update(std::chrono::milliseconds elapsed_time) const;

private:
   Vector<units::Game> pos_;
   std::shared_ptr<Sprite> sprite_;
};

#endif /* FIRST_CAVE_BAT_H_ */
