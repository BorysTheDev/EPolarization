#ifndef INCIDENreal_FIELD_PACKAGE_H_
#define INCIDENreal_FIELD_PACKAGE_H_
#include "incident_field.h"
#include <stdexcept>
#include "types.h"

class IncidentFieldPackage {
public:
	typedef Array<const IncidentField*> IncidentFields;
	//constructors
	explicit IncidentFieldPackage(real waveNumber, size_t size = 1) :
		 fields(size), waveNumber_(waveNumber), filled(0) {}

	//functions
	size_t size() {return fields.size();}
	void addIncidentField(const IncidentField& wave);
	const IncidentField& operator[](const size_t n)const {return *fields[n];}
	const complex operator()(real x1, real x2);
	real waveNumber()const {return waveNumber_;}
	//destructor
	~IncidentFieldPackage();

private:
	IncidentFields fields;
	real waveNumber_;
	size_t filled;
	//this function have not to be used
	typedef IncidentFieldPackage fPack;
	IncidentFieldPackage(const fPack&) = delete;
	const fPack& operator= (const fPack& f) = delete;
};

void IncidentFieldPackage::addIncidentField(const IncidentField& wave){
	if (wave.waveNumber() != waveNumber_)
		throw std::logic_error("not correct wave number");
	fields[filled++] = wave.clone();
}

IncidentFieldPackage::~IncidentFieldPackage(){
	for (size_t i = 0; i < fields.size(); i++){
		if (fields[i]) delete fields[i];
	}
}

const complex IncidentFieldPackage::operator()(real x1, real x2) {
	complex fieldSum = 0;
	for (size_t i = 0; i < size(); i++) {
		fieldSum += (*fields[i])(x1, x2);
	}
	return fieldSum;
}


#endif /* INCIDENreal_FIELD_PACKAGE_H_ */
