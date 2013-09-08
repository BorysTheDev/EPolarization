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
	size_t fieldsNum;
	IncidentFieldPackage &fields;
	real wavenumber;
	std::vector<size_t> discretizionOrder;

	Given(real wavenumber, DonationBox<Curve> &curves,
			IncidentFieldPackage &fields);
};


Given::Given(real wavenumber, DonationBox<Curve> &curves, IncidentFieldPackage &fields):
				curves(curves), fields(fields), wavenumber(wavenumber){
	fieldsNum = fields.size();
	curvesNum = curves.size();
	for (size_t i = 0; i < curvesNum; i++){
		discretizionOrder.push_back(round(5*wavenumber * curves[i].length() / (M_PI) ));
	}
}

typedef Given Params;

#endif
