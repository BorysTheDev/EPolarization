#ifndef DISCRETIZE_CURVE_H_
#define DISCRETIZE_CURVE_H_
#include "array.h"
#include "curve.h"

template<class T>
class DiscretizeCurve{
public:
	template<class PointGen>
	DiscretizeCurve(const Curve<T>& curve, size_t size, PointGen func):
		p_(size), x_(size), y_(size), dx_(size), dy_(size)/*, len(curve.length())*/ {
		for (size_t i = 0; i < size; i++){
			p_[i] = func(size, i);
			x_[i] = curve.x(p_[i]);
			y_[i] = curve.y(p_[i]);
			dx_[i] = curve.dx(p_[i]);
			dy_[i] = curve.dy(p_[i]);
		}
	}

	T p(size_t i) const {return p_[i];}
	T x(size_t i) const {return x_[i];}
	T y(size_t i) const {return y_[i];}
	T dx(size_t i) const {return dx_[i];}
	T dy(size_t i) const {return dy_[i];}

	size_t size() const {return p_.size();}
	//T length() const {return len;}

private:
	Array<T> p_;
	Array<T> x_;
	Array<T> y_;
	Array<T> dx_;
	Array<T> dy_;
	//T len;

	DiscretizeCurve(const DiscretizeCurve&) = delete;
	const DiscretizeCurve& operator= (const DiscretizeCurve&) = delete;
};



#endif /* DISCRETIZE_CURVE_H_ */
