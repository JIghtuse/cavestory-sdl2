#ifndef VARYING_WIDTH_SPRITE_H_
#define VARYING_WIDTH_SPRITE_H_

#include "sprite.h"

struct VaryingWidthSprite : public Sprite {
   VaryingWidthSprite(Graphics& graphics,
        const std::string& file_path,
        const units::Pixel source_x, const units::Pixel source_y,
        const units::Pixel width, const units::Pixel height);
   ~VaryingWidthSprite();

   void set_width(units::Pixel pixels);
};

#endif /* VARYING_WIDTH_SPRITE_H_ */
