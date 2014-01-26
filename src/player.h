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

   struct Jump {
       Jump() : time_remaining_(0), active_(false) {}
       void update(std::chrono::milliseconds elapsed_time);
       void reset();
       void reactivate() { active_ = time_remaining_.count() > 0; }
       void deactivate() { active_ = false; }
       bool is_active() const { return active_; }
   private:
       std::chrono::duration<double,std::milli> time_remaining_;
       bool active_;
   };

   void initializeSprites(Graphics& graphics);
   SpriteState getSpriteState();

   bool is_on_ground() const { return is_on_ground_; }

   Vector<int> pos_;
   Vector<double> velocity_;
   Vector<double> acceleration_;
   HorizontalFacing horizontal_facing_;
   bool is_on_ground_;
   Jump jump_;

   std::map<SpriteState, std::unique_ptr<Sprite> > sprites_;
   static int kTileSize;
};

#endif /* SRC/PLAYER_H_ */
