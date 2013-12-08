#include "discretize_curve.h"
#include <utility>

namespace crv
{

CurveForDiscretize::CurveForDiscretize(const Curve& c) :
  CurveForDiscretize(c, c.length() * 20) {
}

CurveForDiscretize::CurveForDiscretize(const Curve& c, size_t size) :
    curve_(c.clone()), size_(size) {
}

CurveForDiscretize::CurveForDiscretize(const CurveForDiscretize& dc) :
    curve_(dc.curve().clone()), size_(dc.size()) {
}

CurveForDiscretize::CurveForDiscretize(CurveForDiscretize&& cd) :
    curve_(cd.curve_), size_(cd.size_) {
}

CurveForDiscretize& CurveForDiscretize::operator=(CurveForDiscretize& cfd)
{
  curve_ = cfd.curve().clone();
  size_  = cfd.size_;
  return cfd;
}

DiscretizeCurve::DiscretizeCurve(DiscretizeCurve&& dc) : CurveForDiscretize(dc)
{
  points.swap(dc.points);

}

}
