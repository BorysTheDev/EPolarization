#pragma once

#include "curve.h"
#include <vector>

class CubicSpline : public Curve
{
public:
    CubicSpline();

    virtual double x(double t)   const override;
    virtual double y(double t)   const override;
    virtual double dx(double t)  const override;
    virtual double dy(double t)  const override;
    virtual double d2x(double t) const override;
    virtual double d2y(double t) const override;

    virtual types::real length() const override;

    virtual CubicSpline* clone() const override;

};


