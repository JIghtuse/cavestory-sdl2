#ifndef FIRST_CAVE_BAT_H_
#define FIRST_CAVE_BAT_H_

#include <chrono>
#include "damageable.h"
#include "damage_text.h"
#include "vector.h"
#include "units.h"
#include "rectangle.h"
#include "sprite_state.h"

struct Sprite;
struct Graphics;

struct FirstCaveBat : public Damageable {
   FirstCaveBat(Graphics& graphics, Vector<units::Game> pos);
   ~FirstCaveBat();

   void draw(Graphics& graphics) const;
   bool update(const std::chrono::milliseconds elapsed_time,
           const units::Game player_x);

   const Rectangle getDamageRectangle() const;
   const Rectangle getCollisionRectangle() const;

   units::HP contactDamage() const;
   void takeDamage(units::HP damage);

private:
   struct SpriteState {
       SpriteState(HorizontalFacing facing) : facing{facing} {}
       HorizontalFacing facing;
   };
   friend bool operator<(const SpriteState& a, const SpriteState& b) {
       return a.facing < b.facing;
   }

   void initializeSprites(Graphics& graphics);
   void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);
   const SpriteState getSpriteState() const;

   const Vector<units::Game> getCenterPos() const override;
   const std::shared_ptr<DamageText> getDamageText() const override;

   Vector<units::Game> pos_;
   const units::Game flight_center_y_;
   bool alive_;
   HorizontalFacing facing_;
   units::Degrees flight_angle_;
   std::map<SpriteState, std::shared_ptr<Sprite> > sprites_;
   std::shared_ptr<DamageText> damage_text_;
};

#endif /* FIRST_CAVE_BAT_H_ */
