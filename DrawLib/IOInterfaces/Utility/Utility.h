#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>

#ifndef LAMBDA
#define LAMBDA 0.00001
#endif

bool equal(const double& a, const double& b)
{
    return std::abs(a-b) < LAMBDA;
}

#endif // UTILITY_H
