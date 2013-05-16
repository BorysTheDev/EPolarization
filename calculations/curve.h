#ifndef CURVE_H_
#define CURVE_H_
#include "point.h"
#include <cmath>

//TODO it's must be spline or general function
template<class T>
class Curve {
public:
	virtual T x(T t) const = 0;
	virtual T y(T t) const = 0;
	virtual T dx(T t) const = 0;
	virtual T dy(T t) const = 0;

	virtual T length() const = 0;

	virtual Curve* clone() const = 0;

	virtual ~Curve() = default;
};

template<class T>
class Line: public Curve<T> {
public:
	Line(const Point<T>& a, const Point<T>& b);

	T x(T t) const override;
	T y(T t) const override;
	T dx(T t) const override {return cosPhi * len / 2;}
	T dy(T t) const override {return sinPhi * len / 2;}

	T length() const override {return len;}

	Line<T>* clone() const override;

private:
	Point<T> p1;
	Point<T> p2;
	T cosPhi;
	T sinPhi;
	T len;
};

template<class T>
Line<T>::Line(const Point<T>& a, const Point<T>& b): p1(a), p2(b){
		len = sqrt((p2.x - p1.x) * (p2.x - p1.x)
				+ (p2.y - p1.y) * (p2.y - p1.y));
		cosPhi = (p2.x - p1.x) / len;
		sinPhi = (p2.y - p1.y) / len;
}

template<class T>
T Line<T>::x(T t) const {     //given: parameter from -1 to 1
	T t_ = len * (t+1)/2; // correspondence parameter t from 0 to len
	return p1.x + t_ * cosPhi;
}

template<class T>
T Line<T>::y(T t) const {     //given: parameter from -1 to 1
	T t_ = len * (t+1)/2; // correspondence parameter t from 0 to len
	return p1.y + t_ * sinPhi;
}

template<class T>
Line<T>* Line<T>::clone() const {
	return new Line<T>(p1,p2);
}

#endif /* CURVE_H_ */

