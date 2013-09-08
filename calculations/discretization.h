#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_
#include "array.h"
#include "matrix.h"
#include "helper.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "discretize_curve.h"
#include "box.h"
#include "types.h"

class Discretization {
	typedef IncidentFieldPackage IncidentFieldsList;
	typedef Box<DiscretizeCurve> CurvesList;

public:
	Discretization(const CurvesList& sCurves, const IncidentFieldsList& fields);

	MatrixPtr<complex> createMatrix();
	ArrayPtr<complex> createArray();

private:
	size_t size;
	real waveNumber;

	const IncidentFieldsList& fields;
	const CurvesList& curves;

	static void fillMatrixBlock(Matrix<complex>& matr, size_t startI, size_t startJ,
			const DiscretizeCurve& c1, const DiscretizeCurve& c2,real);

};

Discretization::Discretization(const CurvesList& sCurves,
		const IncidentFieldsList& fields) : fields(fields), curves(sCurves) {
	waveNumber = fields.waveNumber();
	size = 0;
	for (size_t i =0; i < sCurves.size(); i++)
		size += sCurves[i].size();
}

MatrixPtr<complex> Discretization::createMatrix() {
	Matrix<complex> *matrix = new Matrix<complex>(size);
	size_t startI = 0;
	for (size_t m = 0; m < curves.size(); m++) {
		size_t startJ = 0;
    for (size_t n = 0; n < curves.size(); n++) {
      fillMatrixBlock(*matrix, startI, startJ,
          curves[m], curves[n], waveNumber);
      startJ += curves[n].size();
		}
		startI += curves[m].size();
	}
	return MatrixPtr<complex>(matrix);
}

ArrayPtr<complex> Discretization::createArray() {
	Array<complex> *f = new Array<complex>(size);
	int ii = 0;
	for (size_t i = 0; i < curves.size(); i++) {
		for (size_t j = 0; j < curves[i].size(); j++, ii++)
			(*f)[ii] = -fields[0](curves[i][j].x, curves[i][j].y);
	}
	return ArrayPtr<complex>(f);
}

void Discretization::fillMatrixBlock(Matrix<complex>& matr,
    size_t i, size_t j, const DiscretizeCurve& c1,
    const DiscretizeCurve& c2, real waveNumber) {
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
        complex temp = ii != jj ? h2(waveNumber * dist(c1[ii], c2[jj]))
          - epol::asymp(c1[ii].t, c1[jj].t) : epol::lim(c1[ii].d, waveNumber);
        matr[i + ii][j + jj] = (M_PI / c1.size())
          * (temp - complex(0, 2) * epol::Ln(c1[ii].t, c1[jj].t, c1.size())
                / M_PI);
      }
    }
  }
}
#endif /* DISCRETIZATION_H_ */
