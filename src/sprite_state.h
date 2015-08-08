#ifndef SPRITE_STATE_H_
#define SPRITE_STATE_H_

#include <map>
#include <memory>

enum class HorizontalFacing {
    FIRST,
    LEFT = FIRST,
    RIGHT,
    LAST,
};

HorizontalFacing& operator++(HorizontalFacing& hf);

enum class VerticalFacing {
    FIRST,
    UP = FIRST,
    DOWN,
    HORIZONTAL,
    LAST,
};

VerticalFacing& operator++(VerticalFacing& vf);

#endif /* SPRITE_STATE_H_ */
