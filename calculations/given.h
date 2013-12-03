#ifndef GIVEN_H_
#define GIVEN_H_
#include "math.h"
#include <vector>
#include "discretize_curve.h"
#include "incident_field.h"
#include "types.h"

struct Given
{
  std::vector<crv::CurveForDiscretize> curves;
  std::vector<ProtoPtr<IncidentField> > fields;
  tps::real wavenumber = 0;
  //size_t curvesNum = 0;
  //size_t fieldsNum = 0;
  //std::vector<size_t> discretizionOrder;
  Given(){}
  Given(tps::real wavenumber, std::vector<crv::CurveForDiscretize> &curves,
      std::vector<ProtoPtr<IncidentField> > &fields);
};

class GivenBuilder
{
public:

  void setWavenumber(tps::real);
  void addCurve(const crv::CurveForDiscretize&);
  void addField(const ProtoPtr<IncidentField>&);

  Given getGiven() const { return given; }

  void reset();
private:
  Given given;
};
typedef Given Params;

#endif /* GIVEN_H_ */
