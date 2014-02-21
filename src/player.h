#ifndef PLAYER_H_
#define PLAYER_H_

#include <chrono>
#include "damage_text.h"
#include "number_sprite.h"
#include "polar_star.h"
#include "sprite.h"
#include "sprite_state.h"
#include "timer.h"
#include "units.h"
#include "varying_width_sprite.h"
#include "vector.h"

struct Graphics;
struct Map;
struct NumberSprite;
struct Rectangle;

struct Player {
   Player(Graphics& graphics, Vector<units::Game> pos);
   ~Player();

   void update(const std::chrono::milliseconds elapsed_time, const Map& map);
   void draw(Graphics& graphics) const;
   void drawHUD(Graphics& graphics) const;

   void startMovingLeft();
   void startMovingRight();
   void stopMoving();

   void lookUp();
   void lookDown();
   void lookHorizontal();

   void startJump();
   void stopJump();

   void takeDamage(units::HP damage);

   const Rectangle getDamageRectangle() const;
   units::Game getCenterX() const {return pos_.x + units::kHalfTile;}
   units::Game getCenterY() const {return pos_.y + units::kHalfTile;}

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
   enum StrideType {
       FIRST_STRIDE_TYPE,
       MIDDLE = FIRST_STRIDE_TYPE,
       LEFT,
       RIGHT,
       LAST_STRIDE_TYPE
   };
   struct SpriteState {
       SpriteState(MotionType motion_type=MotionType::STANDING,
               HorizontalFacing horizontal_facing=HorizontalFacing::LEFT,
               VerticalFacing vertical_facing=VerticalFacing::HORIZONTAL,
               StrideType stride_type=StrideType::MIDDLE
               ) :
           motion_type{motion_type},
           horizontal_facing{horizontal_facing},
           vertical_facing{vertical_facing},
           stride_type{stride_type}
       {}

       MotionType motion_type;
       HorizontalFacing horizontal_facing;
       VerticalFacing vertical_facing;
       StrideType stride_type;
   };
   friend bool operator<(const SpriteState& a, const SpriteState& b);

   struct WalkingAnimation {
       WalkingAnimation();

       StrideType stride() const;
       void update();
   private:
       Timer frame_timer_;
       int current_index_;
       bool forward_;
   };
   units::Tile getFrameX(const SpriteState&) const;
   units::Tile getFrameY(const SpriteState&) const;

   void initializeSprites(Graphics& graphics);
   void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
   const SpriteState getSpriteState() const;

   struct Health {
       Health(Graphics& graphics);
       void update();
       void draw(Graphics& graphics) const;
       // returns true if we have died
       bool takeDamage(units::HP damage);
   private:
       units::Game fillOffset(units::HP health) const;
       units::HP damage_;
       Timer damage_timer_;

       units::HP max_health_;
       units::HP current_health_;
       Sprite health_bar_sprite_;
       VaryingWidthSprite health_fill_bar_sprite_;
       VaryingWidthSprite damage_fill_sprite_;
   };

   const Rectangle leftCollision(units::Game delta) const;
   const Rectangle rightCollision(units::Game delta) const;
   const Rectangle topCollision(units::Game delta) const;
   const Rectangle bottomCollision(units::Game delta) const;

   void updateX(const std::chrono::milliseconds elapsed_time, const Map& map);
   void updateY(const std::chrono::milliseconds elapsed_time, const Map& map);

   bool spriteIsVisible() const;

   bool is_on_ground() const { return is_on_ground_; }

   Vector<units::Game> pos_;
   Vector<units::Velocity> velocity_;
   int acceleration_x_direction_;
   HorizontalFacing horizontal_facing_;
   VerticalFacing vertical_facing_;
   bool is_on_ground_;
   bool is_jump_active_;
   bool is_interacting_;

   Health health_;
   Timer invincible_timer_;
   DamageText damage_text_;

   WalkingAnimation walking_animation_;
   PolarStar polar_star_;

   std::map<SpriteState, std::unique_ptr<Sprite> > sprites_;
};

#endif /* SRC/PLAYER_H_ */
