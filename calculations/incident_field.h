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

template<class T, class N = std::complex<T>>
class IncidentFieldPackage {
public:
	typedef std::vector<const IncidentField<T, N>*> IncidentFields;
	//constructors
	IncidentFieldPackage(T waveNumber) : waveNumber_(waveNumber) {}
	//functions
	size_t size() {return fields.size();}
	template<class Field> void addIncidentField(const Field wave);
	const IncidentField<T, N>& operator[](const size_t n)const {return *fields[n];}
	T waveNumber()const {return waveNumber_;}
	//destructor
	~IncidentFieldPackage();

private:
	IncidentFields fields;
	T waveNumber_;
	//this function have not to be used
	IncidentFieldPackage(const IncidentFieldPackage<T, N>&){}
	const IncidentFieldPackage& operator=(const IncidentFieldPackage<T, N>& f){return f;}
};

template<class T, class N>
template<class Field>
void IncidentFieldPackage<T, N>::addIncidentField(const Field wave){
	if (wave.waveNumber() != waveNumber_) throw std::exception();
	fields.push_back(new decltype(wave)(wave));
}

template<class T, class N>
IncidentFieldPackage<T, N>::~IncidentFieldPackage(){
	for (size_t i = 0; i < fields.size(); i++){
		delete fields[i];
	}
}

template<class T, class N>
N EPolarizationField<T, N>::operator()(T x1, T x2)const {
	T expArg = (x1 * cos(this->alpha_) - x2 * sin(this->alpha_))
			* this->waveNumber_;
	return (-2.0) * exp(N(0, expArg));
}

#endif /* INCIDENT_FIELD_H_ */
