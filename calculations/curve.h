#ifndef CURVE_H_
#define CURVE_H_
#include "point.h"
#include <cmath>
#include "types.h"

//realODO it's must be spline or general function
class Curve {
public:
	virtual real x(real t) const = 0;
	virtual real y(real t) const = 0;
	virtual real dx(real t) const = 0;
	virtual real dy(real t) const = 0;

	virtual real length() const = 0;

	virtual Curve* clone() const = 0;

	virtual ~Curve() = default;
};

class Line: public Curve {
public:
	Line(const Point<real>& a, const Point<real>& b);

	real x(real t) const override;
	real y(real t) const override;
	real dx(real t) const override {return cosPhi * len / 2;}
	real dy(real t) const override {return sinPhi * len / 2;}

	real length() const override {return len;}

	Line* clone() const override;

private:
	Point<real> p1;
	Point<real> p2;
	real cosPhi;
	real sinPhi;
	real len;
};

Line::Line(const Point<real>& a, const Point<real>& b): p1(a), p2(b){
		len = sqrt((p2.x - p1.x) * (p2.x - p1.x)
				+ (p2.y - p1.y) * (p2.y - p1.y));
		cosPhi = (p2.x - p1.x) / len;
		sinPhi = (p2.y - p1.y) / len;
}

real Line::x(real t) const {     //given: parameter from -1 to 1
	real t_ = len * (t+1)/2; // correspondence parameter t from 0 to len
	return p1.x + t_ * cosPhi;
}

real Line::y(real t) const {     //given: parameter from -1 to 1
	real t_ = len * (t+1)/2; // correspondence parameter t from 0 to len
	return p1.y + t_ * sinPhi;
}


Line* Line::clone() const {
	return new Line(p1,p2);
}

class Parabola: public Curve {
public:
	Parabola(const real& x1, const real& x2, const real& p);

	real x(real t) const override;
	real y(real t) const override;
	real dx(real t) const override;
	real dy(real t) const override;

	real length() const override;



	Parabola* clone() const override;

private:
	real x1;
	real x2;
	real p;
	real lengthInt(real x) const;    //Int(sqrt(1+x^2)) which is used for parabola length calculation
};

Parabola::Parabola(const real& x1_, const real& x2_, const real& p_) {
		x1=x1_;
		x2=x2_;
		p=p_;
}

real Parabola::x(real t) const {     //given: parameter from t -1 to 1
	real t_ = x1*(1-t)/2 + x2 * (1+t)/2; // correspondence parameter t_ from x1 to x2
	return t_;
}

real Parabola::y(real t) const {     //given: parameter from t -1 to 1
	real t_ = x1*(1-t)/2 + x2 * (1+t)/2; // correspondence parameter t_ from x1 to x2
	return 1/(2*p)*t_*t_;
}

real Parabola::dx(real t) const {     //given: parameter from t -1 to 1
	return (x2-x1)/2;
}

real Parabola::dy(real t) const {     //given: parameter from t -1 to 1
	real t_ = x1*(1-t)/2 + x2 * (1+t)/2; // correspondence parameter t_ from x1 to x2
	return (t_/p)*(x2-x1)/2;
}

real Parabola::lengthInt(real x) const{
	return 0.5 * (log(sqrt(1 + x * x) + x) + sqrt(1 + x * x) * x);
}

real Parabola::length() const {
	return p*(lengthInt(x2/p) - lengthInt(x1/p));
}

Parabola* Parabola::clone() const {
	return new Parabola(x1,x2,p);
}




#endif /* CURVE_H_ */

