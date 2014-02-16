#ifndef NUMBER_SPRITE_H_
#define NUMBER_SPRITE_H_

#include <memory>
#include <vector>
#include "sprite.h"
#include "units.h"
#include "vector.h"

struct Graphics;

struct NumberSprite {
public:
    static NumberSprite HUDNumber(Graphics& graphics,
            int number,
            int num_digits);
    static NumberSprite DamageNumber(Graphics& graphics, int number);
    static NumberSprite ExperienceNumber(Graphics& graphics, int number);
   ~NumberSprite();

   void draw(Graphics& graphics, Vector<units::Game> pos);

   units::Game getWidth() const;
   units::Game getHeight() const;

private:
   enum class ColorType {
       RED,
       WHITE
   };
   enum class OperatorType {
       PLUS,
       MINUS,
       NONE
   };
   NumberSprite(Graphics& graphics,
           int number,
           int num_digits,
           ColorType color,
           OperatorType op
           );

   OperatorType op_;
   units::Game padding_;
   std::vector<std::shared_ptr<Sprite> > reversed_glyphs_;
};

#endif /* NUMBER_SPRITE_H_ */
