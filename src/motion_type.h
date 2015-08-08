#ifndef MOTION_TYPE_H_
#define MOTION_TYPE_H_

enum class MotionType {
    FIRST,
    STANDING = FIRST,
    INTERACTING,
    WALKING,
    JUMPING,
    FALLING,
    LAST
};

MotionType& operator++(MotionType& mt);

#endif /* MOTION_TYPE_H_ */
