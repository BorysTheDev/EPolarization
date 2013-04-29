#ifndef INCIDENT_FIELD_H_
#define INCIDENT_FIELD_H_
#include "array.h"
#include <exception>
#include <vector>

template<class T, class N = std::complex<T>>
class IncidentField {
public:
	//concstructor
	IncidentField(T waveNumber, T alpha):
			waveNumber_(waveNumber), alpha_(alpha) {}
	//functions
	virtual N operator()(T x1, T x2) const = 0;
	T waveNumber()const {return waveNumber_;}
	//destructor
	virtual ~IncidentField() {
	}
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
	//function
	N operator()(T x1, T x2)const;
};


template<class T, class N>
N EPolarizationField<T, N>::operator()(T x1, T x2)const {
	T expArg = (x1 * cos(this->alpha_) - x2 * sin(this->alpha_))
			* this->waveNumber_;
	return (-2.0) * exp(N(0, expArg));
}

#endif /* INCIDENT_FIELD_H_ */
