#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "units.h"

struct Rectangle {
    Rectangle(units::Game x, units::Game y,
            units::Game width, units::Game height) :
        x_{x},
        y_{y},
        width_{width},
        height_{height}
    {}

    units::Game getLeft() const { return x_; }
    units::Game getRight() const { return x_ + width_; }
    units::Game getTop() const { return y_; }
    units::Game getBottom() const { return y_ + height_; }

    units::Game getWidth() const { return width_; }
    units::Game getHeight() const { return height_; }

private:
    const units::Game x_;
    const units::Game y_;
    const units::Game width_;
    const units::Game height_;
};

#endif /* RECTANGLE_H_ */
