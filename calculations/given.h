#ifndef GIVEN_H_
#define GIVEN_H_
#include <math.h>

template <class T>
struct Given{

	size_t curvesNum;
	CurvePackage<T> &curves;
	size_t fieldsNum;
	IncidentFieldPackage<T> &fields;
	T wavenumber;
	std::vector<size_t> discretizionOrder;

	Given(T wavenumber, CurvePackage<T> &curves, IncidentFieldPackage<T> &fields);
};


template <class T>
Given<T>::Given(T wavenumber, CurvePackage<T> &curves, IncidentFieldPackage<T> &fields):
				curves(curves), fields(fields){
	fieldsNum = fields.size();
	curvesNum = curves.size();
	for (size_t i = 0; i < curvesNum; i++){
		discretizionOrder.push_back(round(5*wavenumber * curves[i].length() / (M_PI) ));
	}
}


#endif
