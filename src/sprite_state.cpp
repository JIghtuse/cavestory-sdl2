#include "sprite_state.h"

HorizontalFacing& operator++(HorizontalFacing& hf) {
    switch (hf) {
        case HorizontalFacing::LEFT: return hf = HorizontalFacing::RIGHT;
        case HorizontalFacing::RIGHT: return hf = HorizontalFacing::LAST;
        case HorizontalFacing::LAST: return hf = HorizontalFacing::LEFT;
    }
    /* should be unavailable */
    return hf;
}

VerticalFacing& operator++(VerticalFacing& vf) {
    switch (vf) {
        case VerticalFacing::UP: return vf = VerticalFacing::DOWN;
        case VerticalFacing::DOWN: return vf = VerticalFacing::HORIZONTAL;
        case VerticalFacing::HORIZONTAL: return vf = VerticalFacing::LAST;
        case VerticalFacing::LAST: return vf = VerticalFacing::UP;
    }
    /* should be unavailable */
    return vf;
}
