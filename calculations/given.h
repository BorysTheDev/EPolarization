#ifndef GIVEN_H_
#define GIVEN_H_
#include "math.h"
#include "box.h"
#include "incident_field_package.h"
#include "curve.h"
#include "types.h"

struct Given{
	size_t curvesNum;
	DonationBox<Curve> &curves;
	int points = 200;
	int threads = 4;
	int tileSize = 30;
	size_t fieldsNum;
	IncidentFieldPackage &fields;
	types::real wavenumber;
	std::vector<size_t> discretizionOrder;

	Given(types::real wavenumber, DonationBox<Curve> &curves,
			IncidentFieldPackage &fields);
};



typedef Given Params;

#endif /* GIVEN_H_ */
