#include "field_solver.h"
#include <iostream>
#include "math/hankel.h"
#include "math/simple_math.h"

using namespace types;
using namespace mth;

complex FieldSolver::field(const RPoint& p) const {
	complex sum = 0;
	for (size_t i = 0; i < curves.size(); i++){
		complex tsum = 0;
        for (size_t j = 0; j < curves[i]->size(); j++) {
            tsum += h2(waveNumber * dist((*curves[i])[j], p)) * currents[i][j];
		}
        sum += tsum * M_PI / (real)curves[i]->size();
	}
	return sum;
}

complex FieldSolver::farField(const real angle) const {
	complex sum = 0;
	for (size_t i = 0; i < curves.size(); i++){
		complex tsum = 0;
        for (size_t j = 0; j < curves[i]->size(); j++) {
            tsum += currents[i][j] * exp(complex(0, waveNumber * ((*curves[i])[j].x *
                    cos(angle) + (*curves[i])[j].y * sin(angle))));
		}
        sum += tsum * M_PI / (real)curves[i]->size();
	}
	return sqrt(2 / (M_PI * waveNumber)) * sum;
}

complex FieldSolver::S4(double psi, const SPCPoint& pt) const
{
    double omega = 1000;
    double e1 = 0.01;
    complex e_arg( 0, waveNumber * (cos(psi) * pt.x + sin(psi) * pt.y) );
    complex coef(0, omega * e1 * (sin(psi) * pt.d.x - cos(psi) * pt.d.y ));
    complex result = coef * exp(e_arg);
    return result;
}

complex FieldSolver::farHField(const real angle) const
{
    double coef = sqr(waveNumber) * sqrt(2) / 60 / curves[0]->size() / sqrt(M_PI * waveNumber);

    complex sum = 0;
    for (int i = 0; i < currents[0].size(); i++)
    {
        sum += S4(angle, (*curves[0])[i]) * currents[0][i];
    }
    return sum * coef / types::complex(0, 4);
}
