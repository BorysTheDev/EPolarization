#ifndef FIELD_SOLVER_H_
#define FIELD_SOLVER_H_

#include "box.h"
#include "discretize_curve.h"
#include "helper.h"
#include "types.h"
#include "array.h"

class FieldSolver {
	typedef Box<DiscretizeCurve> CurvesList;
	typedef Box<Array<complex>> CurrentList;
public:
	FieldSolver(const CurvesList& curves, const CurrentList& currents, double k) :
			curves(curves), currents(currents), waveNumber(k) {
	}
	std::complex<double>  operator()(const Point<double>& p) const ;

private:
	const CurvesList& curves;
	const CurrentList& currents;
	const real waveNumber;
};

complex FieldSolver::operator()(const Point<real>& p) const {
	complex sum = 0;
	for (size_t i = 0; i < curves.size(); i++){
		complex tsum = 0;
		for (size_t j = 0; j < curves[i].size(); j++) {
			tsum += h2(waveNumber * dist(curves[i][j], p)) * currents[i][j];
		}
		sum += tsum * M_PI / (double)curves[i].size();
	}
	return sum;
}


#endif /* FIELD_SOLVER_H_ */
