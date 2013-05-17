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

template<class T>
class Parabola: public Curve<T> {
public:
	Parabola(const T& x1, const T& x2, const T& p);

	T x(T t) const override;
	T y(T t) const override;
	T dx(T t) const override;
	T dy(T t) const override;

	T length() const override;



	Parabola<T>* clone() const override;

private:
	T x1;
	T x2;
	T p;
	T lengthInt(T x) const;    //Int(sqrt(1+x^2)) which is used for parabola length calculation
};

template<class T>
Parabola<T>::Parabola(const T& x1_, const T& x2_, const T& p_) {
		x1=x1_;
		x2=x2_;
		p=p_;
}

template<class T>
T Parabola<T>::x(T t) const {     //given: parameter from t -1 to 1
	T t_ = x1*(1-t)/2 + x2 * (1+t)/2; // correspondence parameter t_ from x1 to x2
	return t_;
}

template<class T>
T Parabola<T>::y(T t) const {     //given: parameter from t -1 to 1
	T t_ = x1*(1-t)/2 + x2 * (1+t)/2; // correspondence parameter t_ from x1 to x2
	return 1/(2*p)*t_*t_;
}

template<class T>
T Parabola<T>::dx(T t) const {     //given: parameter from t -1 to 1
	return (x2-x1)/2;
}


template<class T>
T Parabola<T>::dy(T t) const {     //given: parameter from t -1 to 1
	T t_ = x1*(1-t)/2 + x2 * (1+t)/2; // correspondence parameter t_ from x1 to x2
	return (t_/p)*(x2-x1)/2;
}

template<class T>
T Parabola<T>::lengthInt(T x) const{
	return 0.5 * (log(sqrt(1 + x * x) + x) + sqrt(1 + x * x) * x);
}

template<class T>
T Parabola<T>::length() const {
	return p*(lengthInt(x2/p) - lengthInt(x1/p));
}


template<class T>
Parabola<T>* Parabola<T>::clone() const {
	return new Parabola<T>(x1,x2,p);
}




#endif /* CURVE_H_ */

