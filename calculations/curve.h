#ifndef CURVE_H_
#define CURVE_H_
#include "point.h"
#include <cmath>
#include "types.h"

//realODO it's must be spline or general function
class Curve {
public:
	virtual types::real x(types::real t) const = 0;
	virtual types::real y(types::real t) const = 0;
	virtual types::real dx(types::real t) const = 0;
	virtual types::real dy(types::real t) const = 0;

	virtual types::real length() const = 0;

	virtual Curve* clone() const = 0;

	virtual ~Curve() = default;
};

class Line: public Curve {
public:
	Line(const Point<types::real>& a, const Point<types::real>& b);

	types::real x(types::real t) const override;
	types::real y(types::real t) const override;
	types::real dx(types::real t) const override {return cosPhi * len / 2;}
	types::real dy(types::real t) const override {return sinPhi * len / 2;}

	types::real length() const override {return len;}

	Line* clone() const override;

private:
	types::RPoint p1;
	types::RPoint p2;
	types::real cosPhi;
	types::real sinPhi;
	types::real len;
};


class Parabola: public Curve {
public:
	Parabola(const types::real& x1, const types::real& x2, const types::real& p);

	types::real x(types::real t) const override;
	types::real y(types::real t) const override;
	types::real dx(types::real t) const override;
	types::real dy(types::real t) const override;

	types::real length() const override;



	Parabola* clone() const override;

private:
	types::real x1;
	types::real x2;
	types::real p;
	types::real lengthInt(types::real x) const;    //Int(sqrt(1+x^2)) which is used for parabola length calculation
};






#endif /* CURVE_H_ */

