#include "incident_field_package.h"


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

const tps::complex IncidentFieldPackage::operator()(tps::real x1, tps::real x2) {
	tps::complex fieldSum = 0;
	for (size_t i = 0; i < size(); i++) {
		fieldSum += (*fields[i])(x1, x2);
	}
	return fieldSum;
}
