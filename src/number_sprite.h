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
   NumberSprite(Graphics& graphics, int number, int num_digits=0);
   ~NumberSprite();

   void draw(Graphics& graphics, Vector<units::Game> pos);
private:
   units::Game padding_;
   std::vector<std::shared_ptr<Sprite> > reversed_digits_;
};

#endif /* NUMBER_SPRITE_H_ */
