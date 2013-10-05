#include "given.h"

Given::Given(types::real wavenumber, DonationBox<Curve> &curves, IncidentFieldPackage &fields):
				curves(curves), fields(fields), wavenumber(wavenumber){
	fieldsNum = fields.size();
	curvesNum = curves.size();
	for (size_t i = 0; i < curvesNum; i++){
		discretizionOrder.push_back(round(5*wavenumber * curves[i].length() / (M_PI) ));
	}
}
