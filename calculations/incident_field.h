#ifndef INCIDENreal_FIELD_H_
#define INCIDENreal_FIELD_H_
#include "array.h"
#include <vector>
#include "types.h"

class IncidentField {
public:
	//constructor
	IncidentField(real waveNumber, real alpha):
			waveNumber_(waveNumber), alpha_(alpha) {}

	//functions
	virtual complex operator()(real x1, real x2) const = 0;

	virtual IncidentField* clone() const = 0;

	real waveNumber()const {return waveNumber_;}

	//destructor
	virtual ~IncidentField() = default;

protected:
	real waveNumber_;
	real alpha_;
};

class EPolarizationField: public IncidentField {
public:
	//constructor
	EPolarizationField(real waveNumber, real alpha) :
			IncidentField(waveNumber, alpha) {}

	//functions
	complex operator()(real x1, real x2)const override;

	EPolarizationField* clone() const override {
		return new EPolarizationField(this->waveNumber_, this->alpha_);}
};


complex EPolarizationField::operator()(real x1, real x2)const {
	real expArg = (x1 * cos(this->alpha_) + x2 * sin(this->alpha_))
			* this->waveNumber_;
	return exp(complex(0, -expArg));
}

#endif /* INCIDENreal_FIELD_H_ */
