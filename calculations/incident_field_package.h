#ifndef INCIDENT_FIELD_PACKAGE_H_
#define INCIDENT_FIELD_PACKAGE_H_
#include "incident_field.h"
#include <stdexcept>

template<class T, class N = std::complex<T>>
class IncidentFieldPackage {
public:
	typedef Array<const IncidentField<T, N>*> IncidentFields;
	//constructors
	explicit IncidentFieldPackage(T waveNumber, size_t size = 1) :
		 fields(size), waveNumber_(waveNumber), filled(0) {}

	//functions
	size_t size() {return fields.size();}
	void addIncidentField(const IncidentField<T, N>& wave);
	const IncidentField<T, N>& operator[](const size_t n)const {return *fields[n];}
	const N operator()(T x1, T x2);
	T waveNumber()const {return waveNumber_;}
	//destructor
	~IncidentFieldPackage();

private:
	IncidentFields fields;
	T waveNumber_;
	size_t filled;
	//this function have not to be used
	typedef IncidentFieldPackage<T, N> fPack;
	IncidentFieldPackage(const fPack&) = delete;
	const fPack& operator= (const fPack& f) = delete;
};

template<class T, class N>
void IncidentFieldPackage<T, N>::addIncidentField(const IncidentField<T, N>& wave){
	if (wave.waveNumber() != waveNumber_)
		throw std::logic_error("not correct wave number");
	fields[filled++] = wave.clone();
}

template<class T, class N>
IncidentFieldPackage<T, N>::~IncidentFieldPackage(){
	for (size_t i = 0; i < fields.size(); i++){
		if (fields[i]) delete fields[i];
	}
}

template<class T, class N>
const N IncidentFieldPackage<T, N>::operator()(T x1, T x2) {
	N fieldSum = 0;
	for (size_t i = 0; i < size(); i++) {
		fieldSum += fields[i](x1, x2);
	}
	return fieldSum;
}


#endif /* INCIDENT_FIELD_PACKAGE_H_ */
