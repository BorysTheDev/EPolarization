#ifndef INCIDENT_FIELD_H_
#define INCIDENT_FIELD_H_
#include "array.h"
#include <vector>
#include "types.h"

class IncidentField {
public:
	//constructor
	IncidentField(tps::real waveNumber, tps::real alpha):
			waveNumber_(waveNumber), alpha_(alpha) {}

	//functions
	virtual tps::complex operator()(tps::real x1, tps::real x2) const = 0;

	virtual IncidentField* clone() const = 0;

	tps::real waveNumber()const {return waveNumber_;}

	//destructor
	virtual ~IncidentField() = default;

protected:
	tps::real waveNumber_;
	tps::real alpha_;
};

class EPolarizationField: public IncidentField {
public:
	//constructor
	EPolarizationField(tps::real waveNumber, tps::real alpha) :
			IncidentField(waveNumber, alpha) {}

	//functions
	tps::complex operator()(tps::real x1, tps::real x2)const override;

	EPolarizationField* clone() const override {
		return new EPolarizationField(this->waveNumber_, this->alpha_);}
};



#endif /* INCIDENT_FIELD_H_ */
