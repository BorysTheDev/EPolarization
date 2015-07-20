#ifndef GIVEN_H_
#define GIVEN_H_
#include "math.h"
#include "incident_field_package.h"
#include "curve.h"
#include "types.h"
#include <vector>
#include <memory>

struct Given{
	size_t curvesNum;
    std::vector<Curve::Ptr>&& curves;
    int points = 40;
	int threads = 4;
    int tileSize = 60;
	size_t fieldsNum;
	IncidentFieldPackage &fields;
	types::real wavenumber;
	std::vector<size_t> discretizionOrder;

    Given(types::real wavenumber,  std::vector<Curve::Ptr> &&curves,
			IncidentFieldPackage &fields);
};

typedef Given Params;

#endif /* GIVEN_H_ */
