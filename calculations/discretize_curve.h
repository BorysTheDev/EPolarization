#ifndef DISCRETIZE_CURVE_H_
#define DISCRETIZE_CURVE_H_
#include "array.h"
#include "curve.h"

template<class T>
struct ParametricCurvePoint: public Point<T>
{
  T t;        //parameter
  Point<T> d; //derivative
};

template<class T>
class DiscretizeCurve{
public:
	template<class PointGen>
	DiscretizeCurve(const Curve<T>&, size_t size, PointGen func);

	ParametricCurvePoint<T> operator[](size_t i) const {return points[i];}
	size_t size() const {return points.size();}

private:
	Array<ParametricCurvePoint<T>> points;
	DiscretizeCurve(const DiscretizeCurve&) = delete;
	const DiscretizeCurve& operator= (const DiscretizeCurve&) = delete;
};

template<class T>
template<class PointGen>
DiscretizeCurve<T>::DiscretizeCurve(const Curve<T>& curve,
    size_t size, PointGen func) : points(size)
{
  for (size_t i = 0; i < size; i++) {
    points[i].t = func(size, i);
    points[i].x = curve.x(points[i].t);
    points[i].y = curve.y(points[i].t);
    points[i].d.x = curve.dx(points[i].t);
    points[i].d.y = curve.dy(points[i].t);
  }
}

#endif /* DISCRETIZE_CURVE_H_ */
