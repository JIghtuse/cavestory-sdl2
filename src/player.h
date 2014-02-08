#ifndef PLAYER_H_
#define PLAYER_H_

#include <chrono>
#include <map>
#include <memory>
#include "sprite.h"
#include "vector.h"
#include "units.h"

struct Graphics;
struct Map;
struct Rectangle;

struct Player {
   Player(Graphics& graphics, Vector<units::Game> pos);
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

   units::Game getCenterX() const {return pos_.x + units::tileToGame(1) / 2.0;}

private:
   enum class MotionType {
       FIRST_MOTION_TYPE,
       STANDING = FIRST_MOTION_TYPE,
       INTERACTING,
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
   units::Tile getFrameX(const SpriteState&) const;
   units::Tile getFrameY(const SpriteState&) const;

   void initializeSprites(Graphics& graphics);
   void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
   SpriteState getSpriteState();

   Rectangle leftCollision(units::Game delta) const;
   Rectangle rightCollision(units::Game delta) const;
   Rectangle topCollision(units::Game delta) const;
   Rectangle bottomCollision(units::Game delta) const;

   void updateX(std::chrono::milliseconds elapsed_time, const Map& map);
   void updateY(std::chrono::milliseconds elapsed_time, const Map& map);

   bool is_on_ground() const { return is_on_ground_; }

   Vector<units::Game> pos_;
   Vector<units::Velocity> velocity_;
   int acceleration_x_direction_;
   HorizontalFacing horizontal_facing_;
   VerticalFacing vertical_facing_;
   bool is_on_ground_;
   bool is_jump_active_;
   bool is_interacting_;

   std::map<SpriteState, std::unique_ptr<Sprite> > sprites_;
};

#endif /* SRC/PLAYER_H_ */
