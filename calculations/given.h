#ifndef GIVEN_H_
#define GIVEN_H_
#include <math.h>

template <class T>
struct Given{
	size_t curvesNum;
	DonationBox<Curve<T>> &curves;
	size_t fieldsNum;
	IncidentFieldPackage<T> &fields;
	T wavenumber;
	std::vector<size_t> discretizionOrder;

	Given(T wavenumber, DonationBox<Curve<T>> &curves,
			IncidentFieldPackage<T> &fields);
};


template <class T>
Given<T>::Given(T wavenumber, DonationBox<Curve<T>> &curves, IncidentFieldPackage<T> &fields):
				curves(curves), fields(fields), wavenumber(wavenumber){
	fieldsNum = fields.size();
	curvesNum = curves.size();
	for (size_t i = 0; i < curvesNum; i++){
		discretizionOrder.push_back(round(5*wavenumber * curves[i].length() / (M_PI) ));
	}
}

typedef Given<double> Params;

#endif
