#include "given.h"
#include "helper.h"

Given::Given(types::real wavenumber, std::vector<Curve::Ptr> &&curves, IncidentFieldPackage &fields):
                curves(std::move(curves)), fields(fields), wavenumber(wavenumber){
	fieldsNum = fields.size();
	curvesNum = curves.size();
	for (size_t i = 0; i < curvesNum; i++){
        discretizionOrder.push_back((uint32_t)round(5*wavenumber * curves[i]->length() / (M_PI) ));
	}
}
