#ifndef DISCRETIZE_CURVE_H_
#define DISCRETIZE_CURVE_H_
#include "array.h"
#include "curve.h"

template<class T>
struct ParametricCurvePoint: public Point<real>
{
  T t;        //parameter
  Point<real> d; //derivative
};

class DiscretizeCurve{
public:
	template<class PointGen>
	DiscretizeCurve(const Curve&, size_t size, PointGen func);

	ParametricCurvePoint<real> operator[](size_t i) const {return points[i];}
	size_t size() const {return points.size();}

private:
	Array<ParametricCurvePoint<real>> points;
	DiscretizeCurve(const DiscretizeCurve&) = delete;
	const DiscretizeCurve& operator= (const DiscretizeCurve&) = delete;
};

template<class PointGen>
DiscretizeCurve::DiscretizeCurve(const Curve& curve,
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
