#ifndef STRIDE_TYPE_H_
#define STRIDE_TYPE_H_

enum StrideType {
    FIRST,
    MIDDLE = FIRST,
    LEFT,
    RIGHT,
    LAST
};

StrideType& operator++(StrideType& st);

#endif /* STRIDE_TYPE_H_ */
