#ifndef CURVE_H_
#define CURVE_H_
#include "point.h"
#include <cmath>

//TODO you must make it how incident field class
template<class T>
class Curve {
public:
	virtual T x(T t) = 0;
	virtual T y(T t) = 0;
	virtual T dx(T t) = 0;
	virtual T dy(T t) = 0;

	virtual Curve* clone() = 0;

	virtual ~Curve() = default;
};

template<class T>
class Line: public Curve<T> {
public:
	Line(const Point<T>& a, const Point<T>& b);
	Curve<T>* clone();

private:
	Point<T> p1;
	Point<T> p2;
	T cosPhi;
	T sinPhi;
	T len;
	T x(T t);
	T y(T t);
	T dx(T t) {return cosPhi * len / 2;}
	T dy(T t) {return sinPhi * len / 2;}


};

template<class T>
Line<T>::Line(const Point<T>& a, const Point<T>& b): p1(a), p2(b){
		len = sqrt((p2.x - p1.x) * (p2.x - p1.x)
				+ (p2.y - p1.y) * (p2.y - p1.y));
		cosPhi = (p2.x - p1.x) / len;
		sinPhi = (p2.y - p1.y) / len;
}

template<class T>
T Line<T>::x(T t){     //given: parameter from -1 to 1
	T t_ = len * (t+1)/2; // correspondence parameter t from 0 to len
	return p1.x + t_*cosPhi;
}

template<class T>
T Line<T>::y(T t){     //given: parameter from -1 to 1
	T t_ = len* (t+1)/2; // correspondence parameter t from 0 to len
	return p1.y + t_*sinPhi;
}

template<class T>
Curve<T>* Line<T>::clone() {
	return new Line<T>(p1,p2);
}

#endif /* CURVE_H_ */

