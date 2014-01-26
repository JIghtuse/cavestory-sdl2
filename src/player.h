#ifndef PLAYER_H_
#define PLAYER_H_

#include <chrono>
#include <map>
#include <memory>
#include "sprite.h"
#include "vector.h"

struct Graphics;

struct Player {
   Player(Graphics& graphics, Vector<int> pos);
   ~Player();

   void update(std::chrono::milliseconds elapsed_time);
   void draw(Graphics& graphics);

   void startMovingLeft();
   void startMovingRight();
   void stopMoving();

   void startJump();
   void stopJump();

private:
   enum class MotionType {
       STANDING,
       WALKING
   };
   enum class HorizontalFacing {
       LEFT,
       RIGHT
   };
   struct SpriteState {
       SpriteState(MotionType motion_type=MotionType::STANDING,
               HorizontalFacing horizontal_facing=HorizontalFacing::LEFT) :
           motion_type(motion_type),
           horizontal_facing(horizontal_facing) {}

       MotionType motion_type;
       HorizontalFacing horizontal_facing;
   };
   friend bool operator<(const SpriteState& a, const SpriteState& b);

   void initializeSprites(Graphics& graphics);
   SpriteState getSpriteState();

   Vector<int> pos_;
   Vector<double> velocity_;
   Vector<double> acceleration_;
   HorizontalFacing horizontal_facing_;
   std::map<SpriteState, std::unique_ptr<Sprite> > sprites_;
   static int kTileSize;
};

#endif /* SRC/PLAYER_H_ */
