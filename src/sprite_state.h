#ifndef SPRITE_STATE_H_
#define SPRITE_STATE_H_

#include <map>
#include <memory>

#define ENUM_CLASS(enum_class) enum_class

#define ENUM_FOREACH(var, enum_class, enum_name)         \
    for (int var = (int) ENUM_CLASS(enum_class)::FIRST_##enum_name; \
            var < (int) ENUM_CLASS(enum_class)::LAST_##enum_name;   \
            ++var)

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

#endif /* SPRITE_STATE_H_ */

