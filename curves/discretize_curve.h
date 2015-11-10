#ifndef DISCRETIZE_CURVE_H_
#define DISCRETIZE_CURVE_H_
#include "curve.h"
#include <vector>

template<class T>
struct ParametricCurvePoint: public Point<T>
{
    T t;        //parameter
    Point<T> d; //derivative
    Point<T> d2;
};

typedef ParametricCurvePoint<double> const SPCPoint;

class DiscretizeCurve{
public:
    typedef std::unique_ptr<DiscretizeCurve> Ptr;

    template<class PointGen>
    DiscretizeCurve(const Curve&, size_t size, PointGen func);

    const ParametricCurvePoint<types::real>& operator[](size_t i) const {return points[i];}
    size_t size() const {return points.size();}

private:
    std::vector<ParametricCurvePoint<types::real>> points;
    DiscretizeCurve(const DiscretizeCurve&) = delete;
    const DiscretizeCurve& operator=(const DiscretizeCurve&) = delete;
};

template<class PointGen>
DiscretizeCurve::DiscretizeCurve(const Curve& curve, size_t size, PointGen func) : points(size)
{
    for (size_t i = 0; i < size; i++) {
        points[i].t = func(size, i);
        points[i].x = curve.x(points[i].t);
        points[i].y = curve.y(points[i].t);
        points[i].d.x = curve.dx(points[i].t);
        points[i].d.y = curve.dy(points[i].t);
        points[i].d2.x = curve.d2x(points[i].t);
        points[i].d2.y = curve.d2y(points[i].t);
    }
}

#endif /* DISCRETIZE_CURVE_H_ */
