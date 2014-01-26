#ifndef PLAYER_H_
#define PLAYER_H_

#include <chrono>
#include <map>
#include <memory>
#include "sprite.h"

struct Graphics;

struct Player {
   Player(Graphics& graphics, int x, int y);
   ~Player();

   void update(std::chrono::duration<double,std::milli> elapsed_time);
   void draw(Graphics& graphics);

   void startMovingLeft();
   void startMovingRight();
   void stopMoving();

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

   int x_;
   int y_;
   double velocity_x_;
   double acceleration_x_;
   HorizontalFacing horizontal_facing_;
   std::map<SpriteState, std::unique_ptr<Sprite> > sprites_;
   static int kTileSize;
};

#endif /* SRC/PLAYER_H_ */
