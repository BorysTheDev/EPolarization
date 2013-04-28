#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_
#include "curve.h"
#include <vector>
#include "helper.h"
#include "incident_field.h"

template<class T, class N = std::complex<T>>
class Discretization {
	typedef IncidentFieldPackage<T> IncidentFieldsList;
	typedef std::vector<Curve<T>*> CurvesList;
public:
	Discretization(CurvesList curves, IncidentFieldsList fields):fields(fields)
	{
		waveNumber = fields.waveNumber();
		size= round(waveNumber/M_PI) * 10;
		this->curves = curves;
	}

	Matrix<N> createMatrix() {
		Matrix<N> matrix(size);
			for (size_t i = 0; i < size; i++) {
				for (size_t j = 0; j < size; j++) {
					matrix[i][j] = (M_PI / size)
							* (K(t_(size, i), t_(size, j))
									+ N(0, 2 * Ln(t_(size, i), t_(size, j), size) / M_PI));
				}
			}
			return matrix;
	}

	//TODO
	Array<complex> createArray() {
		Array<complex> f(size);
		for (size_t i = 0; i < size; i++) {
			double xx1 = curves[0]->x1(t_(size, i));
			double xx2 = curves[0]->x2(t_(size, i));
			f[i] = complex(0, 2) * fields[0](xx1, xx2);
		}
		return f;
	}

private:
	size_t size;
	T waveNumber;

	CurvesList curves;
	IncidentFieldsList fields;

	//TODO
	complex K(const double& t, const double& tau_) {
		double tau = t == tau_ ? tau_ + epsilant : tau_;
		double sqrtArg = pow(curves[0]->x1(t) - curves[0]->x1(tau), 2)
				+ pow(curves[0]->x2(t) - curves[0]->x2(tau), 2);
		return h1(waveNumber * sqrt(sqrtArg)) - complex(0, 2 * log(fabs(t - tau)) / M_PI);
	}

	double Ln(const double t0, double const t_,const int n) {
		double sum = 0;
		for (int p = 1; p < n; p++) {
			sum += chebyshevcalculate(p, t_) * chebyshevcalculate(p, t0) / p;
		}
		return -(log(2) + 2 * sum);
	}

	double chebyshevcalculate(int n, double x){
		return cos(n * acos(x));
	}

	double t_(const int n, const int i){
		return cos((2.0 * i + 1.0) * M_PI / (2.0 * n));
	}

	complex h1(const double& x) {
		return complex(_j0(x), y0(x));
	}

};

#endif /* DISCRETIZATION_H_ */
