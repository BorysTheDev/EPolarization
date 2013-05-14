#ifndef INCIDENT_FIELD_H_
#define INCIDENT_FIELD_H_
#include "array.h"
#include <vector>

template<class T, class N = std::complex<T>>
class IncidentField {
public:
	//constructor
	IncidentField(T waveNumber, T alpha):
			waveNumber_(waveNumber), alpha_(alpha) {}

	//functions
	virtual N operator()(T x1, T x2) const = 0;

	virtual IncidentField* clone() const = 0;

	T waveNumber()const {return waveNumber_;}

	//destructor
	virtual ~IncidentField() = default;

protected:
	T waveNumber_;
	T alpha_;
};

template<class T, class N = std::complex<T>>
class EPolarizationField: public IncidentField<T> {
public:
	//constructor
	EPolarizationField(T waveNumber, T alpha) :
			IncidentField<T>(waveNumber, alpha) {}

	//functions
	N operator()(T x1, T x2)const override;

	EPolarizationField* clone() const override {
		return new EPolarizationField(this->waveNumber_, this->alpha_);}
};


template<class T, class N>
N EPolarizationField<T, N>::operator()(T x1, T x2)const {
	T expArg = (x1 * cos(this->alpha_) + x2 * sin(this->alpha_))
			* this->waveNumber_;
	return exp(N(0, -expArg));
}

#endif /* INCIDENT_FIELD_H_ */
