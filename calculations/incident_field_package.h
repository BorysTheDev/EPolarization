#ifndef INCIDENT_FIELD_PACKAGE_H_
#define INCIDENT_FIELD_PACKAGE_H_
#include <stdexcept>
#include "incident_field.h"

template<class T, class N = std::complex<T>>
class IncidentFieldPackage {
public:
	typedef Array<const IncidentField<T, N>*> IncidentFields;
	//constructors
	IncidentFieldPackage(T waveNumber, size_t size = 1) :
		 fields(size), waveNumber_(waveNumber), filled(0) {}
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
	size_t filled;
	//this function have not to be used
	IncidentFieldPackage(const IncidentFieldPackage<T, N>&)
		{throw std::logic_error("prohibited function in IncidentFieldPackage");}
	const IncidentFieldPackage& operator=(const IncidentFieldPackage<T, N>& f)
		{throw std::logic_error("prohibited function in IncidentFieldPackage");}
};

template<class T, class N>
template<class Field>
void IncidentFieldPackage<T, N>::addIncidentField(const Field wave){
	if (wave.waveNumber() != waveNumber_) throw std::exception();
	fields[filled++] = new decltype(wave)(wave);
}

template<class T, class N>
IncidentFieldPackage<T, N>::~IncidentFieldPackage(){
	for (size_t i = 0; i < fields.size(); i++){
		delete fields[i];
	}
}


#endif /* INCIDENT_FIELD_PACKAGE_H_ */
