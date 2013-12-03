#include "discretization.h"


Discretization::Discretization(const CurvesList& sCurves,
		const IncidentFieldsList& fields) : fields(fields), curves(sCurves) {
	waveNumber = fields[0]->waveNumber();
	size = 0;
	for (size_t i =0; i < sCurves.size(); i++)
		size += sCurves[i].size();
}

MatrixPtr<tps::complex> Discretization::createMatrix() {
	Matrix<tps::complex> *matrix = new Matrix<tps::complex>(size);
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
	return MatrixPtr<tps::complex>(matrix);
}

ArrayPtr<tps::complex> Discretization::createArray() {
	Array<tps::complex> *f = new Array<tps::complex>(size);
	int ii = 0;
	for (size_t i = 0; i < curves.size(); i++) {
		for (size_t j = 0; j < curves[i].size(); j++, ii++)
			(*f)[ii] = -(*fields[0])(curves[i][j].x, curves[i][j].y);
	}
	return ArrayPtr<tps::complex>(f);
}

void Discretization::fillMatrixBlock(Matrix<tps::complex>& matr,
    size_t i, size_t j, const crv::DiscretizeCurve& c1,
    const crv::DiscretizeCurve& c2, tps::real waveNumber) {
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
    	  tps::complex temp = ii != jj ? h2(waveNumber * dist(c1[ii], c2[jj]))
          - epol::asymp(c1[ii].t, c1[jj].t) : epol::lim(c1[ii].d, waveNumber);
        matr[i + ii][j + jj] = (M_PI / c1.size())
          * (temp - tps::complex(0, 2) * epol::Ln(c1[ii].t, c1[jj].t, c1.size())
                / M_PI);
      }
    }
  }
}
