#ifndef CURVE_H_
#define CURVE_H_
#include "point.h"
#include <cmath>
#include "types.h"
#include "prototype.h"

namespace crv
{

class Curve : public Prototype<Curve> {
public:
	virtual tps::real x(tps::real t) const = 0;
	virtual tps::real y(tps::real t) const = 0;
	virtual tps::real dx(tps::real t) const = 0;
	virtual tps::real dy(tps::real t) const = 0;
	virtual tps::real d2x(tps::real t) const = 0;
	virtual tps::real d2y(tps::real t) const = 0;

	virtual tps::real length() const = 0;
};

class Line: public Curve {
public:
	Line(const tps::RPoint& a, const tps::RPoint& b);

	tps::real x(tps::real t) const override;
	tps::real y(tps::real t) const override;
	tps::real dx(tps::real t) const override {return cosPhi * len / 2;}
	tps::real dy(tps::real t) const override {return sinPhi * len / 2;}
	tps::real d2x(tps::real t) const override {return 0;};
	tps::real d2y(tps::real t) const override {return 0;};

	tps::real length() const override {return len;}

	Line* clone() const override;

private:
	tps::RPoint p1;
	tps::RPoint p2;
	tps::real cosPhi;
	tps::real sinPhi;
	tps::real len;
};

//TODO change derivative
class Parabola: public Curve {
public:
	Parabola(const tps::real& x1, const tps::real& x2, const tps::real& p);

	tps::real x(tps::real t) const override;
	tps::real y(tps::real t) const override;
	tps::real dx(tps::real t) const override;
	tps::real dy(tps::real t) const override;
  tps::real d2x(tps::real t) const override;
  tps::real d2y(tps::real t) const override;

	tps::real length() const override;

	Parabola* clone() const override;

private:
	tps::real x1;
	tps::real x2;
	tps::real p;
	tps::real lengthInt(tps::real x) const;    //Int(sqrt(1+x^2)) which is used for parabola length calculation
};

}




#endif /* CURVE_H_ */

