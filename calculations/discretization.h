#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_
#include "curve.h"
#include <vector>
#include "matrix.h"
#include "helper.h"
#include "incident_field.h"
#include "incident_field_package.h"

template<class T, class N = std::complex<T>>
class Discretization {
	typedef IncidentFieldPackage<T> IncidentFieldsList;
	typedef std::vector<Curve<T>*> CurvesList;
public:
	Discretization(CurvesList curves, const IncidentFieldsList& fields):fields(fields)
	{
		waveNumber = fields.waveNumber();
		size= round(waveNumber/M_PI) * 10;
		this->curves = curves;
	}

	MatrixPtr<N> createMatrix() {
		Matrix<N>* matrix = new Matrix<N>(size);
			for (size_t i = 0; i < size; i++) {
				for (size_t j = 0; j < size; j++) {
					(*matrix)[i][j] = (M_PI / size) * (K(t_(size, i), t_(size, j))
						+ N(0, 2 * Ln(t_(size, i), t_(size, j), size) / M_PI));
				}
			}
			return MatrixPtr<N>(matrix);
	}

	//TODO
	ArrayPtr<N> createArray() {
		Array<N>* f = new Array<N>(size);
		for (size_t i = 0; i < size; i++) {
			(*f)[i] = N(0, 2) * fields[0](curves[0]->x1(t_(size, i)),
					curves[0]->x2(t_(size, i)));
		}
		return ArrayPtr<N>(f);
	}

private:
	size_t size;
	T waveNumber;

	CurvesList curves;
	const IncidentFieldsList& fields;

	//TODO
	N K(const double& t, const double& tau_) {
		double tau = t == tau_ ? tau_ + epsilant : tau_;
		double sqrtArg = pow(curves[0]->x1(t) - curves[0]->x1(tau), 2)
				+ pow(curves[0]->x2(t) - curves[0]->x2(tau), 2);
		return h1(waveNumber * sqrt(sqrtArg)) - N(0, 2 * log(fabs(t - tau)) / M_PI);
	}

	double Ln(const double t0, double const t_,const int n) {
		double sum = 0;
		for (int p = 1; p < n; p++) {
			sum += ch1(p, t_) * ch1(p, t0) / p;
		}
		return -(log(2) + 2 * sum);
	}

	double t_(const int n, const int i){
		return cos((2.0 * i + 1.0) * M_PI / (2.0 * n));
	}

	N h1(const double& x) {
		return N(j0(x),y0(x));
	}

};

#endif /* DISCRETIZATION_H_ */
