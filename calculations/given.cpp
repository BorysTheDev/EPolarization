#include "given.h"
#include "helper.h"

Given::Given(tps::real wavenumber, std::vector<crv::CurveForDiscretize>& curves,
    std::vector<ProtoPtr<IncidentField> > &fields) :
    curves(curves), fields(fields), wavenumber(wavenumber)
{
  //fieldsNum = fields.size();
  //curvesNum = curves.size();
  //for (size_t i = 0; i < curvesNum; i++) {
  //discretizionOrder.push_back(
  //    (uint32_t) round(5 * wavenumber * curves[i].size() / (M_PI)));
  //}
}

void GivenBuilder::setWavenumber(tps::real wn)
{
  for (auto& a : given.fields)
    a->setWaveNumber(wn);
  given.wavenumber = wn;
}

void GivenBuilder::addCurve(const crv::CurveForDiscretize& curve)
{
  given.curves.push_back(curve);
}

void GivenBuilder::addField(const ProtoPtr<IncidentField>& field)
{
  if (given.fields.size()) {
    given.fields.push_back(field);
    given.wavenumber = field->waveNumber();
  } else if (given.wavenumber == field->waveNumber()) {
    given.fields.push_back(field);
  } else
    throw std::logic_error("fields wavenumbers must be equal");
}

void GivenBuilder::reset()
{
  given = Given();
}
