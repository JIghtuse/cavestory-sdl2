#ifndef PLAYER_H_
#define PLAYER_H_

#include <chrono>
#include <map>
#include <memory>
#include "sprite.h"
#include "vector.h"

struct Graphics;
struct Map;
struct Rectangle;

struct Player {
   Player(Graphics& graphics, Vector<int> pos);
   ~Player();

   void update(std::chrono::milliseconds elapsed_time, const Map& map);
   void draw(Graphics& graphics);

   void startMovingLeft();
   void startMovingRight();
   void stopMoving();

   void lookUp();
   void lookDown();
   void lookHorizontal();

   void startJump();
   void stopJump();

private:
   enum class MotionType {
       FIRST_MOTION_TYPE,
       STANDING = FIRST_MOTION_TYPE,
       WALKING,
       JUMPING,
       FALLING,
       LAST_MOTION_TYPE
   };
   enum class HorizontalFacing {
       FIRST_HORIZONTAL_FACING,
       LEFT = FIRST_HORIZONTAL_FACING,
       RIGHT,
       LAST_HORIZONTAL_FACING
   };
   enum class VerticalFacing {
       FIRST_VERTICAL_FACING,
       UP = FIRST_VERTICAL_FACING,
       DOWN,
       HORIZONTAL,
       LAST_VERTICAL_FACING
   };
   struct SpriteState {
       SpriteState(MotionType motion_type=MotionType::STANDING,
               HorizontalFacing horizontal_facing=HorizontalFacing::LEFT,
               VerticalFacing vertical_facing=VerticalFacing::HORIZONTAL) :
           motion_type(motion_type),
           horizontal_facing(horizontal_facing),
           vertical_facing(vertical_facing) {}

       MotionType motion_type;
       HorizontalFacing horizontal_facing;
       VerticalFacing vertical_facing;
   };
   friend bool operator<(const SpriteState& a, const SpriteState& b);
   int getFrameX(const SpriteState&) const;
   int getFrameY(const SpriteState&) const;

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
   void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
   SpriteState getSpriteState();

   Rectangle leftCollision(int delta) const;
   Rectangle rightCollision(int delta) const;
   Rectangle topCollision(int delta) const;
   Rectangle bottomCollision(int delta) const;

   bool is_on_ground() const { return is_on_ground_; }

   Vector<int> pos_;
   Vector<double> velocity_;
   Vector<double> acceleration_;
   HorizontalFacing horizontal_facing_;
   VerticalFacing vertical_facing_;
   bool is_on_ground_;
   Jump jump_;

   std::map<SpriteState, std::unique_ptr<Sprite> > sprites_;
   static int kTileSize;
};

#endif /* SRC/PLAYER_H_ */
