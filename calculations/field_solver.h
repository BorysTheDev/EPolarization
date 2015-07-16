#ifndef FIELD_SOLVER_H_
#define FIELD_SOLVER_H_

#include "discretize_curve.h"
#include "types.h"
#include "helper.h"

class FieldSolver {
    typedef std::vector<DiscretizeCurve::Ptr> CurvesList;
    typedef std::vector<std::vector<types::complex>> CurrentList;
public:
	FieldSolver(const CurvesList& curves, const CurrentList& currents,
			types::real k) : curves(curves), currents(currents), waveNumber(k) {
	}
	types::complex field(const types::RPoint& p) const;

	types::complex farField(const types::real angle) const;
private:

	const CurvesList& curves;
	const CurrentList& currents;
	const types::real waveNumber;
};




#endif /* FIELD_SOLVER_H_ */
