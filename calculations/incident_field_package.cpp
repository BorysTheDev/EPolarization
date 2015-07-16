#include "incident_field_package.h"

using namespace types;

void IncidentFieldPackage::addIncidentField(const IncidentField& wave)
{
  if (wave.waveNumber() != waveNumber_)
    throw std::logic_error("not correct wave number");
  fields.emplace_back(wave.clone());
}

IncidentFieldPackage::~IncidentFieldPackage()
{
}

const complex IncidentFieldPackage::operator()(real x1, real x2) const
{
  types::complex fieldSum = 0;
  for (size_t i = 0; i < size(); i++) {
    fieldSum += (*fields[i])(x1, x2);
  }
  return fieldSum;
}
