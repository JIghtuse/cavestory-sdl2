#include "motion_type.h"

MotionType& operator++(MotionType& mt) {
   switch (mt) {
       case MotionType::STANDING: return mt = MotionType::INTERACTING;
       case MotionType::INTERACTING: return mt = MotionType::WALKING;
       case MotionType::WALKING: return mt = MotionType::JUMPING;
       case MotionType::JUMPING: return mt = MotionType::FALLING;
       case MotionType::FALLING: return mt = MotionType::LAST;
       case MotionType::LAST: return mt = MotionType::STANDING;
   }
   /* should be unavailable */
   return mt;
}
