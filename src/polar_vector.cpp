#include "polar_vector.h"

const Vector<units::Game> PolarVector::getPos() const
{
    return Vector<units::Game> {
        magnitude_ * units::cos(angle_),
        magnitude_ * units::sin(angle_),
    };
}
