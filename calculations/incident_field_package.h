#ifndef INCIDENT_FIELD_PACKAGE_H_
#define INCIDENT_FIELD_PACKAGE_H_
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
	typedef IncidentFieldPackage<T, N> fPack;
	IncidentFieldPackage(const fPack&) = delete;
	const fPack& operator= (const fPack& f) = delete;
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
		if (fields[i]) delete fields[i];
	}
}


#endif /* INCIDENT_FIELD_PACKAGE_H_ */
