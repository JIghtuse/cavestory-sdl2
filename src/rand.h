#ifndef RAND_H_
#define RAND_H_

#include <random>
#include "units.h"

double rand_double(double low, double high)
{
    static std::random_device rd;
    static std::default_random_engine re(rd());
    static std::uniform_real_distribution<double> u(low, high);
    return u(re);
}

units::Degrees rand_angle()
{
    static std::random_device rd;
    static std::default_random_engine re(rd());
    static std::uniform_real_distribution<double> u(0.0, 360.0);
    return u(re);
}

#endif /* RAND_H_ */
