#ifndef POLAR_VECTOR_H_
#define POLAR_VECTOR_H_

#include "units.h"
#include "vector.h"

struct PolarVector {
    PolarVector( units::Game magnitude, units::Degrees angle) :
        magnitude_{magnitude},
        angle_{angle}
    {}
    const Vector<units::Game> getPos() const;

    units::Game getMagnitude() const { return magnitude_; }
    units::Degrees getAngle() const { return angle_; }

    void setMagnitude(units::Game magnitude) { magnitude_ = magnitude; }
    void setAngle(units::Degrees angle) { angle_ = angle; }
private:
    units::Game magnitude_;
    units::Degrees angle_;
};

#endif /* POLAR_VECTOR_H_ */

