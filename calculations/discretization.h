#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_
#include "curve.h"
#include "array.h"
#include "matrix.h"
#include "helper.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "curve_package.h"
#include "discretize_curve.h"

template<class T, class N = std::complex<T>>
class Discretization {
	typedef IncidentFieldPackage<T> IncidentFieldsList;
	typedef CurvePackage<T> CurvesList;
	typedef Array<DiscretizeCurve<T>*> DiscretizeCurves;
	//delete
	int discSize;
public:
	Discretization(const CurvesList& sCurves, const IncidentFieldsList& fields) :
			simpleCurves(sCurves), fields(fields), curves(sCurves.size()) {
		waveNumber = fields.waveNumber();
		discSize = round(waveNumber / M_PI) * 2;
		size = curves.size() * discSize;
		for (size_t i = 0; i < curves.size(); i++)
			curves[i] = new DiscretizeCurve<T>(simpleCurves[i], discSize,
					ch1Nodes);
	}

	MatrixPtr<N> createMatrix() {
		Matrix<N>* matrix = new Matrix<N>(size);
		size_t startI = 0;
		for (size_t m = 0; m < curves.size(); m++) {
			size_t endI = startI + curves[m]->size();
			size_t startJ = 0;
			for (size_t n = 0; n < curves.size(); n++) {
				size_t endJ = startJ + curves[n]->size();
				size_t i = startI;
				if (m == n) {
					for (size_t ii = 0; i < endI; i++, ii++) {
						size_t j = startJ;
						for (size_t jj = 0; j < endJ; j++, jj++) {
							N temp = ii != jj ?
									 kernel(curves[m]->x(ii), curves[m]->y(ii),
											curves[n]->x(jj), curves[n]->y(jj))
									 - asymp(curves[m]->p(ii), curves[n]->p(jj))
									 : lim(curves[n]->dx(ii), curves[n]->dy(ii));
							(*matrix)[i][j] = (M_PI / curves[n]->size()) *
									(temp - N(0, 2)
									* Ln(curves[m]->p(ii), curves[m]->p(jj),
											curves[m]->size()) / M_PI);
						}
					}
				} else {
					for (size_t ii = 0; i < endI; i++, ii++) {
						size_t j = startJ;
						for (size_t jj = 0; j < endJ; j++, jj++) {
							(*matrix)[i][j] = (M_PI / curves[n]->size())
									* kernel(curves[m]->x(ii), curves[m]->y(ii),
											curves[n]->x(jj), curves[n]->y(jj));
						}
					}
				}
				startJ = endJ;
			}
			startI = endI;
		}
		for (size_t i = 0; i < matrix->width(); i++) {
			for (size_t j = 0; j < matrix->width(); j++)
				std::cout << (*matrix)[i][j] << "  ";
			std::cout << std::endl;
		}
		return MatrixPtr<N>(matrix);
	}

	//TODO
	ArrayPtr<N> createArray() {
		Array<N>* f = new Array<N>(size);
		int ii = 0;
		for (size_t i = 0; i < curves.size(); i++) {
			for (size_t j = 0; j < curves[i]->size(); j++, ii++)
				(*f)[ii] = -fields[0](curves[i]->x(j), curves[i]->y(j));
		}
		return ArrayPtr<N>(f);
	}

private:
	size_t size;
	T waveNumber;

	const CurvesList& simpleCurves;
	const IncidentFieldsList& fields;
	DiscretizeCurves curves;

	const double gamma = 0.57721566490153;

	inline N kernel(const T& x1, const T& x2, const T& y1, const T &y2) {
		return h2(waveNumber * sqrt(sqr(x1 - y1) + sqr(x2 - y2)));
	}

	inline N asymp(const T& t, const T& tau) {
		return -(N(0, 2 * log(fabs(t - tau)) / M_PI));
	}

	inline N lim(T dx, T dy) {
		return -N(0, 2 / M_PI)
				* (log(waveNumber * sqrt(sqr(dx) + sqr(dy)) / 2) - M_PI / N(0, 2) + gamma);
	}

	double Ln(const double& t0, double const& t_, const int n) {
		double sum = 0;
		for (int p = 1; p < n; p++) {
			sum += ch1(p, t_) * ch1(p, t0) / p;
		}
		return -(log(2) + 2 * sum);
	}

};

#endif /* DISCRETIZATION_H_ */
