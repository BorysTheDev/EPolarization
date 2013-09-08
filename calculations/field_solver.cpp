#include "field_solver.h"
#include <iostream>
using namespace types;

complex FieldSolver::field(const RPoint& p) const {
	complex sum = 0;
	for (size_t i = 0; i < curves.size(); i++){
		complex tsum = 0;
		for (size_t j = 0; j < curves[i].size(); j++) {
			tsum += h2(waveNumber * dist(curves[i][j], p)) * currents[i][j];
		}
		sum += tsum * M_PI / (real)curves[i].size();
	}
	return sum;
}

complex FieldSolver::farField(const real angle) const {
	complex sum = 0;
	for (size_t i = 0; i < curves.size(); i++){
		complex tsum = 0;
		for (size_t j = 0; j < curves[i].size(); j++) {
			tsum += currents[i][j] * exp(complex(0, waveNumber * (curves[i][j].x *
					cos(angle) + curves[i][j].y * sin(angle))));
		}
		sum += tsum * M_PI / (real)curves[i].size();
	}
	return sqrt(2 / (M_PI * waveNumber)) * sum;
}
