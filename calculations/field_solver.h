#ifndef FIELD_SOLVER_H_
#define FIELD_SOLVER_H_

#include "box.h"
#include "discretize_curve.h"
#include "helper.h"

template<class T, class N = std::complex<T>>
class FieldSolver {
	typedef Box<DiscretizeCurve<T>> CurvesList;
	typedef Box<Array<N> > CurrentList;
public:
	FieldSolver(const CurvesList& curves, const CurrentList& currents, T k) :
			curves(curves), currents(currents), waveNumber(k) {
	}
	N operator()(const T& x, const T& y) const ;

private:
	const CurvesList& curves;
	const CurrentList& currents;
	const T waveNumber;
};

template<class T, class N>
N FieldSolver<T, N>::operator()(const T& x, const T& y) const {
	N sum = 0;
	for (size_t i = 0; i < curves.size(); i++){
		N tsum = 0;
		for (size_t j = 0; j < curves[i].size(); j++) {
			tsum += epol::kernel(curves[i][j].x, curves[i][j].y,
					x, y, waveNumber) * currents[i][j];
		}
		sum += tsum * M_PI / (double)curves[i].size();
	}
	return sum;
}


#endif /* FIELD_SOLVER_H_ */
