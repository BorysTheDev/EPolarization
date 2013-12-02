#ifndef DISCRETIZE_CURVE_H_
#define DISCRETIZE_CURVE_H_
#include "curve.h"
#include <memory>
#include <vector>

namespace crv
{

struct ParametricCurvePoint: public tps::RPoint
{
  tps::real t;        //parameter
  tps::RPoint d;      //derivative
  tps::RPoint d2;     //2-d derivative
};

class CurveForDiscretize
{
public:
  CurveForDiscretize(const Curve&, size_t size);
  CurveForDiscretize(const CurveForDiscretize&);
  CurveForDiscretize(CurveForDiscretize&&);
  CurveForDiscretize& operator=(CurveForDiscretize&);

  const Curve& curve() const    { return *curve_; }
  size_t size() const           { return size_; }
  void setSize(size_t size)     { size_ = size; }

protected:
  std::unique_ptr<const Curve> curve_;
  int size_;
};

class DiscretizeCurve : public CurveForDiscretize{
public:
  typedef ParametricCurvePoint pcp;

  DiscretizeCurve(DiscretizeCurve&&);
	template<class PointGen>
	DiscretizeCurve(const Curve&, size_t size, PointGen func);
  template<class PointGen>
	DiscretizeCurve(const CurveForDiscretize&, PointGen func);

	pcp operator[](size_t i) const { return points[i]; }

private:
	std::vector<pcp> points;
	DiscretizeCurve(const DiscretizeCurve&) = delete;
	const DiscretizeCurve& operator= (const DiscretizeCurve&) = delete;
};

template<class PointGen>
DiscretizeCurve::DiscretizeCurve(const Curve& curve,
    size_t size, PointGen func) : CurveForDiscretize(curve, size), points(size)
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

template<class PointGen>
DiscretizeCurve::DiscretizeCurve(const CurveForDiscretize& dc, PointGen f) :
  DiscretizeCurve(dc.curve(), dc.size(), f) {
}


}

#endif /* DISCRETIZE_CURVE_H_ */
