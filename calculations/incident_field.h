#ifndef INCIDENT_FIELD_H_
#define INCIDENT_FIELD_H_
#include <vector>
#include "types.h"

class IncidentField {
public:
	//constructor
	IncidentField(types::real waveNumber, types::real alpha):
			waveNumber_(waveNumber), alpha_(alpha) {}

	//functions
	virtual types::complex operator()(types::real x1, types::real x2) const = 0;

	virtual IncidentField* clone() const = 0;

	types::real waveNumber()const {return waveNumber_;}

	//destructor
	virtual ~IncidentField() = default;

protected:
	types::real waveNumber_;
	types::real alpha_;
};

class EPolarizationField: public IncidentField {
public:
	//constructor
	EPolarizationField(types::real waveNumber, types::real alpha) :
			IncidentField(waveNumber, alpha) {}

	//functions
	types::complex operator()(types::real x1, types::real x2)const override;

	EPolarizationField* clone() const override {
		return new EPolarizationField(this->waveNumber_, this->alpha_);}
};



#endif /* INCIDENT_FIELD_H_ */
