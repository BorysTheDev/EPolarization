#include "discretization.h"

Discretization::Discretization(const CurvesList& sCurves,
		const IncidentFields& fields) : fields(fields), curves(sCurves),
		wN(fields.waveNumber()), borders(sCurves.size())
{
	for (size_t i = 0; i < sCurves.size(); i++) {
		size += sCurves[i].size();
		borders[i] = size;
	}
}

MatrixPtr<types::complex> Discretization::createMatrix() {
	Matrix<types::complex> *matrix = new Matrix<types::complex>(size);
	for (size_t m = 0; m < curves.size(); m++) {
    for (size_t n = 0; n < curves.size(); n++) {
      fillMatrixBlock(*matrix, m, n);
		}
	}
	return MatrixPtr<types::complex>(matrix);
}

ArrayPtr<types::complex> Discretization::createArray() {
	Array<types::complex> *f = new Array<types::complex>(size);
	int ii = 0;
	for (size_t i = 0; i < curves.size(); i++) {
		for (size_t j = 0; j < curves[i].size(); j++, ii++)
			(*f)[ii] = -fields(curves[i][j].x, curves[i][j].y);
	}
	return ArrayPtr<types::complex>(f);
}

void Discretization::fillMatrixBlock(Matrix<types::complex>& matr,
    size_t ci1, size_t ci2) {

  const DiscretizeCurve& c1 = curves[ci1];
  const DiscretizeCurve& c2 = curves[ci2];

  if (ci1 != ci2) {
    //not diagonal blocks
    for (int ii = leftBorderOf(ci1); ii < borders[ci1]; ii++) {
      for (int jj = leftBorderOf(ci2); jj < borders[ci2]; jj++) {
        matr[ii][jj] = (M_PI / c2.size()) * h2(wN * dist(c1[ii] ,c2[jj]));
      }
    }
  } else {
    //diagonal block
    for (int ii = leftBorderOf(ci1); ii < borders[ci1]; ii++) {
      for (int jj = leftBorderOf(ci2); jj < borders[ci2]; jj++) {
    	  types::complex temp = ii != jj ? h2(wN * dist(c1[ii], c2[jj]))
          - epol::asymp(c1[ii].t, c1[jj].t) : epol::lim(c1[ii].d, wN);
        matr[ii][jj] = (M_PI / c1.size()) * (temp - types::complex(0, 2) *
            epol::Ln(c1[ii].t, c1[jj].t, c1.size()) / M_PI);
      }
    }
  }
}
