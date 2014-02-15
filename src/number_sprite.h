#ifndef NUMBER_SPRITE_H_
#define NUMBER_SPRITE_H_

#include <memory>
#include "sprite.h"
#include "units.h"
#include "vector.h"

struct Graphics;

struct NumberSprite {
public:
   NumberSprite(Graphics& graphics, int number);
   ~NumberSprite();

   void draw(Graphics& graphics, Vector<units::Game> pos);
private:
   std::shared_ptr<Sprite> sprite_;
};

#endif /* NUMBER_SPRITE_H_ */
