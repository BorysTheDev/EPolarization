#include "ellipse.h"
#include <cassert>

using namespace types;

//given: parameter from t -1 to 1

CEllipse::CEllipse(double a, double b)
{
    A = a;
    B = b;
}

real CEllipse::x(real t) const
{
    return A * cos(t);
}

real CEllipse::y(real t) const
{
    return B * sin(t);
}

real CEllipse::dx(real t) const
{
    return -A * sin(t);
}

real CEllipse::dy(real t) const
{
    return B * cos(t);
}

real CEllipse::d2x(real t) const
{
    return 0;
}

real CEllipse::d2y(real t) const
{
    return 0;
}

real CEllipse::length() const
{
    return 0;
}

CEllipse* CEllipse::clone() const
{
    return new CEllipse(A, B);
}
