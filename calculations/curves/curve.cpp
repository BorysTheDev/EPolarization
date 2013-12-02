#include "curve.h"

using namespace tps;
namespace crv {

Line::Line(const tps::RPoint& a, const tps::RPoint& b) :
    p1(a), p2(b)
{
  len = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
  cosPhi = (p2.x - p1.x) / len;
  sinPhi = (p2.y - p1.y) / len;
}

real Line::x(real t) const          //given: parameter from -1 to 1
{     //given: parameter from -1 to 1
  real t_ = len * (t + 1) / 2; // correspondence parameter t from 0 to len
  return p1.x + t_ * cosPhi;
}

real Line::y(real t) const          //given: parameter from -1 to 1
{
  real t_ = len * (t + 1) / 2; // correspondence parameter t from 0 to len
  return p1.y + t_ * sinPhi;
}

Line* Line::clone() const
{
  return new Line(p1, p2);
}

Parabola::Parabola(const real& x1_, const real& x2_, const real& p_)
{
  x1 = x1_;
  x2 = x2_;
  p = p_;
}

real Parabola::x(real t) const      //given: parameter from -1 to 1
{
  real t_ = x1 * (1 - t) / 2 + x2 * (1 + t) / 2; // correspondence parameter t_ from x1 to x2
  return t_;
}

real Parabola::y(real t) const      //given: parameter from -1 to 1
{
  real t_ = x1 * (1 - t) / 2 + x2 * (1 + t) / 2; // correspondence parameter t_ from x1 to x2
  return 1 / (2 * p) * t_ * t_;
}

real Parabola::dx(real t) const     //given: parameter from -1 to 1
{
  return (x2 - x1) / 2;
}

real Parabola::dy(real t) const     //given: parameter from t -1 to 1
{
  real t_ = x1 * (1 - t) / 2 + x2 * (1 + t) / 2; // correspondence parameter t_ from x1 to x2
  return (t_ / p) * (x2 - x1) / 2;
}

real Parabola::d2x(real t) const    //given: parameter from -1 to 1
{
  return 0;
}
real Parabola::d2y(real t) const    //given: parameter from -1 to 1
{
  return (x2 - x1) * (x2 - x1) / (4 * p);
}

real Parabola::lengthInt(real x) const
{
  return 0.5 * (log(sqrt(1 + x * x) + x) + sqrt(1 + x * x) * x);
}

real Parabola::length() const
{
  return p * (lengthInt(x2 / p) - lengthInt(x1 / p));
}

Parabola* Parabola::clone() const
{
  return new Parabola(x1, x2, p);
}

}
