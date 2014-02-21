#ifndef POLAR_STAR_H_
#define POLAR_STAR_H_

#include "sprite_state.h"
#include "units.h"
#include "vector.h"

struct Graphics;
struct Sprite;

struct PolarStar {
   PolarStar(Graphics& graphics);
   ~PolarStar();

   void draw(Graphics& graphics,
        HorizontalFacing horizontal_facing, VerticalFacing vertical_facing,
        bool gun_up,
        Vector<units::Game> pos) const;
private:
   struct SpriteState {
       SpriteState(
               HorizontalFacing horizontal_facing,
               VerticalFacing vertical_facing
               ) :
           horizontal_facing{horizontal_facing},
           vertical_facing{vertical_facing}
       {}

       HorizontalFacing horizontal_facing;
       VerticalFacing vertical_facing;
   };
   friend bool operator<(const SpriteState& a, const SpriteState& b);

   void initializeSprites(Graphics& graphics);
   void initializeSprite(Graphics& graphics, const SpriteState& sprite_state);

   std::map<SpriteState, std::shared_ptr<Sprite> > sprite_map_;
};

#endif /* POLAR_STAR_H_ */

