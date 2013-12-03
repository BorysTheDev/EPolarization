#ifndef GIVEN_H_
#define GIVEN_H_
#include "math.h"
#include <vector>
#include "discretize_curve.h"
#include "incident_field.h"
#include "types.h"

struct Given
{
  size_t curvesNum;
  std::vector<crv::CurveForDiscretize> curves;
  size_t fieldsNum;
  std::vector<ProtoPtr<IncidentField> > fields;
  tps::real wavenumber;
  std::vector<size_t> discretizionOrder;

  Given(tps::real wavenumber, std::vector<crv::CurveForDiscretize> &curves,
      std::vector<ProtoPtr<IncidentField> > &fields);
};

class GivenBuilder
{
public:
  void reset();
private:
  Given given;
};
typedef Given Params;

#endif /* GIVEN_H_ */
