#ifndef INCIDENreal_FIELD_PACKAGE_H_
#define INCIDENreal_FIELD_PACKAGE_H_
#include "incident_field.h"
#include <stdexcept>
#include "types.h"

class IncidentFieldPackage {
public:
	typedef Array<const IncidentField*> IncidentFields;
	//constructors
	explicit IncidentFieldPackage(types::real waveNumber, size_t size = 1) :
		 fields(size), waveNumber_(waveNumber), filled(0) {}

	//functions
	size_t size() const {return fields.size();}
	void addIncidentField(const IncidentField& wave);
	const IncidentField& operator[](const size_t n)const {return *fields[n];}
	const types::complex operator()(types::real x1, types::real x2) const;
	types::real waveNumber()const {return waveNumber_;}
	//destructor
	~IncidentFieldPackage();

private:
	IncidentFields fields;
	types::real waveNumber_;
	size_t filled;
	//this function have not to be used
	typedef IncidentFieldPackage fPack;
	IncidentFieldPackage(const fPack&) = delete;
	const fPack& operator= (const fPack& f) = delete;
};



#endif /* INCIDENreal_FIELD_PACKAGE_H_ */
