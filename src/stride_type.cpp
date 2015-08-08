#include "stride_type.h"

StrideType& operator++(StrideType& st) {
   switch (st) {
       case StrideType::MIDDLE: return st = StrideType::LEFT;
       case StrideType::LEFT: return st = StrideType::RIGHT;
       case StrideType::RIGHT: return st = StrideType::LAST;
       case StrideType::LAST: return st = StrideType::MIDDLE;
   }
   /* should be unavailable */
   return st;
}
