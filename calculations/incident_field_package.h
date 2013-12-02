#ifndef INCIDENreal_FIELD_PACKAGE_H_
#define INCIDENreal_FIELD_PACKAGE_H_
#include "incident_field.h"
#include <stdexcept>
#include "types.h"

class IncidentFieldPackage {
public:
	typedef Array<const IncidentField*> IncidentFields;
	//constructors
	explicit IncidentFieldPackage(tps::real waveNumber, size_t size = 1) :
		 fields(size), waveNumber_(waveNumber), filled(0) {}

	//functions
	size_t size() {return fields.size();}
	void addIncidentField(const IncidentField& wave);
	const IncidentField& operator[](const size_t n)const {return *fields[n];}
	const tps::complex operator()(tps::real x1, tps::real x2);
	tps::real waveNumber()const {return waveNumber_;}
	//destructor
	~IncidentFieldPackage();

private:
	IncidentFields fields;
	tps::real waveNumber_;
	size_t filled;
	//this function have not to be used
	typedef IncidentFieldPackage fPack;
	IncidentFieldPackage(const fPack&) = delete;
	const fPack& operator= (const fPack& f) = delete;
};



#endif /* INCIDENreal_FIELD_PACKAGE_H_ */
