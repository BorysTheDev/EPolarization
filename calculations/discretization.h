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

public:
	Discretization(const CurvesList& sCurves, const IncidentFieldsList& fields);

	MatrixPtr<N> createMatrix();
	ArrayPtr<N> createArray();

private:
	size_t size;
	T waveNumber;

	const CurvesList& simpleCurves;
	const IncidentFieldsList& fields;
	DiscretizeCurves curves;

	void fillAnotherMatrixBlock(Matrix<N>& matr, size_t startI, size_t startJ,
			const DiscretizeCurve<T>& c1, const DiscretizeCurve<T>& c2);

	void fillMiddleMatrixBlock(Matrix<N>& matr, size_t startI,
			const DiscretizeCurve<T>& c1);

	//adapter for functions
	N kernel(const DiscretizeCurve<T>& c, size_t i, size_t j) {
		return epol::kernel(c.x(i), c.y(i), c.x(j), c.y(j), waveNumber);
	}

	//adapter for functions
	N kernel(const DiscretizeCurve<T>& c1, size_t i,
			const DiscretizeCurve<T>& c2, size_t j) {
		return epol::kernel(c1.x(i), c1.y(i), c2.x(j), c2.y(j), waveNumber);
	}

	//adapter for functions
	N asymp(const DiscretizeCurve<T>& curve, size_t i, size_t j) {
		return epol::asymp(curve.p(i), curve.p(j));
	}

	//adapter for functions
	N lim(const DiscretizeCurve<T>& curve, size_t i) {
		return epol::lim(curve.dx(i), curve.dy(i), waveNumber);
	}

	//adapter for functions
	N Ln(const DiscretizeCurve<T>& curve, size_t i, size_t j) {
		return epol::Ln(curve.p(i), curve.p(j), curve.size());
	}
};

template<class T, class N>
Discretization<T, N>::Discretization(const CurvesList& sCurves,
		const IncidentFieldsList& fields) :
		simpleCurves(sCurves), fields(fields), curves(sCurves.size()) {
	waveNumber = fields.waveNumber();
	int discSize = round(waveNumber / M_PI) * 2;
	size = curves.size() * discSize;
	for (size_t i = 0; i < curves.size(); i++)
		curves[i] = new DiscretizeCurve<T>(simpleCurves[i], discSize, ch1Nodes);
}

template<class T, class N>
MatrixPtr<N> Discretization<T, N>::createMatrix() {
	Matrix<N> *matrix = new Matrix<N>(size);
	size_t startI = 0;
	for (size_t m = 0; m < curves.size(); m++) {
		size_t startJ = 0;
		for (size_t n = 0; n < curves.size(); n++) {
			if (m == n) {
				fillMiddleMatrixBlock(*matrix, startI, *curves[n]);
			} else {
				fillAnotherMatrixBlock(*matrix, startI, startJ, *curves[m],
						*curves[n]);
			}
			startJ += curves[n]->size();
		}
		startI += curves[m]->size();
	}
	return MatrixPtr<N>(matrix);
}

template<class T, class N>
ArrayPtr<N> Discretization<T, N>::createArray() {
	Array<N> *f = new Array<N>(size);
	int ii = 0;
	for (size_t i = 0; i < curves.size(); i++) {
		for (size_t j = 0; j < curves[i]->size(); j++, ii++)
			(*f)[ii] = -fields[0](curves[i]->x(j), curves[i]->y(j));
	}
	return ArrayPtr<N>(f);
}

template<class T, class N>
void Discretization<T, N>::fillAnotherMatrixBlock(Matrix<N>& matr,
		size_t startI, size_t startJ, const DiscretizeCurve<T>& c1,
		const DiscretizeCurve<T>& c2) {
	size_t i = startI;
	for (size_t ii = 0; ii < c1.size(); i++, ii++) {
		size_t j = startJ;
		for (size_t jj = 0; jj < c2.size(); j++, jj++) {
			matr[i][j] = (M_PI / c2.size()) * kernel(c1, ii, c2, jj);
		}
	}
}

template<class T, class N>
void Discretization<T, N>::fillMiddleMatrixBlock(Matrix<N>& matr, size_t startI,
		const DiscretizeCurve<T>& c1) {
	size_t i = startI;
	for (size_t ii = 0; ii < c1.size(); i++, ii++) {
		size_t j = startI;
		for (size_t jj = 0; jj < c1.size(); j++, jj++) {
			N temp =
					ii != jj ?
							kernel(c1, ii, jj) - asymp(c1, ii, jj) :
							lim(c1, ii);
			matr[i][j] = (M_PI / c1.size())
					* (temp - N(0, 2) * Ln(c1, ii, jj) / M_PI);
		}
	}
}
#endif /* DISCRETIZATION_H_ */
