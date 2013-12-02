#ifndef GIVEN_H_
#define GIVEN_H_
#include "math.h"
#include <vector>
#include "incident_field_package.h"
#include "discretize_curve.h"
#include "types.h"

struct Given
{
  size_t curvesNum;
  std::vector<crv::CurveForDiscretize> curves;
  size_t fieldsNum;
  IncidentFieldPackage &fields;
  tps::real wavenumber;
  std::vector<size_t> discretizionOrder;

  Given(tps::real wavenumber, std::vector<crv::CurveForDiscretize>& curves,
      IncidentFieldPackage &fields);
};

class GivenBuilder
{
public:

private:
  Given given;
};
typedef Given Params;

#endif /* GIVEN_H_ */
