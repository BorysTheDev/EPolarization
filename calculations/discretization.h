#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_
#include "array.h"
#include "matrix.h"
#include "helper.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "discretize_curve.h"
#include "box.h"

template<class T, class N = std::complex<T>>
class Discretization {
	typedef IncidentFieldPackage<T> IncidentFieldsList;
	typedef Box<DiscretizeCurve<T>> CurvesList;

public:
	Discretization(const CurvesList& sCurves, const IncidentFieldsList& fields);

	MatrixPtr<N> createMatrix();
	ArrayPtr<N> createArray();

private:
	size_t size;
	T waveNumber;


	const IncidentFieldsList& fields;
	const CurvesList& curves;

	void fillMatrixBlock(Matrix<N>& matr, size_t startI, size_t startJ,
			const DiscretizeCurve<T>& c1, const DiscretizeCurve<T>& c2);

	//adapter for functions
	N asymp(const DiscretizeCurve<T>& curve, size_t i, size_t j) {
		return epol::asymp(curve[i].t, curve[j].t);
	}

	//adapter for functions
	N lim(const DiscretizeCurve<T>& curve, size_t i) {
		return epol::lim(curve[i].d.x, curve[i].d.y, waveNumber);
	}

	//adapter for functions
	N Ln(const DiscretizeCurve<T>& curve, size_t i, size_t j) {
		return epol::Ln(curve[i].t, curve[j].t, curve.size());
	}
};

template<class T, class N>
Discretization<T, N>::Discretization(const CurvesList& sCurves,
		const IncidentFieldsList& fields) : fields(fields), curves(sCurves) {
	waveNumber = fields.waveNumber();
	size = 0;
	for (size_t i =0; i < sCurves.size(); i++)
		size += sCurves[i].size();
}

template<class T, class N>
MatrixPtr<N> Discretization<T, N>::createMatrix() {
	Matrix<N> *matrix = new Matrix<N>(size);
	size_t startI = 0;
	for (size_t m = 0; m < curves.size(); m++) {
		size_t startJ = 0;
    for (size_t n = 0; n < curves.size(); n++) {
      fillMatrixBlock(*matrix, startI, startJ, curves[m], curves[n]);

      startJ += curves[n].size();
		}
		startI += curves[m].size();
	}
	return MatrixPtr<N>(matrix);
}

template<class T, class N>
ArrayPtr<N> Discretization<T, N>::createArray() {
	Array<N> *f = new Array<N>(size);
	int ii = 0;
	for (size_t i = 0; i < curves.size(); i++) {
		for (size_t j = 0; j < curves[i].size(); j++, ii++)
			(*f)[ii] = -fields[0](curves[i][j].x, curves[i][j].y);
	}
	return ArrayPtr<N>(f);
}

template<class T, class N>
void Discretization<T, N>::fillMatrixBlock(Matrix<N>& matr,
    size_t i, size_t j, const DiscretizeCurve<T>& c1,
    const DiscretizeCurve<T>& c2) {
  if (i != j) {
    //not diagonal blocks
    for (size_t ii = 0; ii < c1.size(); ii++) {
      for (size_t jj = 0; jj < c2.size(); jj++) {
        matr[i + ii][j + jj] = (M_PI / c2.size())
            * h2(waveNumber * dist(c1[ii] ,c2[jj]));
      }
    }
  } else {
    //diagonal block
    for (size_t ii = 0; ii < c1.size(); ii++) {
      for (size_t jj = 0; jj < c1.size(); jj++) {
        N temp = ii != jj ? h2(waveNumber * dist(c1[ii], c2[jj]))
            - asymp(c1, ii, jj) : lim(c1, ii);
        matr[i + ii][j + jj] = (M_PI / c1.size())
            * (temp - N(0, 2) * Ln(c1, ii, jj) / M_PI);
      }
    }
  }
}
#endif /* DISCRETIZATION_H_ */
