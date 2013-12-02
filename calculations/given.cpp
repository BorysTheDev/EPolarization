#include "given.h"
#include "helper.h"

Given::Given(tps::real wavenumber,
    std::vector<crv::CurveForDiscretize>& curves, IncidentFieldPackage &fields) :
    curves(curves), fields(fields), wavenumber(wavenumber)
{
  fieldsNum = fields.size();
  curvesNum = curves.size();
  for (size_t i = 0; i < curvesNum; i++) {
    discretizionOrder.push_back(
        (uint32_t) round(5 * wavenumber * curves[i].size() / (M_PI)));
  }
}
