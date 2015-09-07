#pragma once

#include "curve.h"

class CEllipse : public Curve
{
public:
    CEllipse(const double a, const double b);

    virtual double x(double t)   const override;
    virtual double y(double t)   const override;
    virtual double dx(double t)  const override;
    virtual double dy(double t)  const override;
    virtual double d2x(double t) const override;
    virtual double d2y(double t) const override;

    virtual types::real length() const override;

    virtual CEllipse* clone()    const override;

private:
    double A;
    double B;
};



