#ifndef MT_DISCRETIZATION_H_
#define MT_DISCRETIZATION_H_
#include "array.h"
#include "matrix.h"
#include "helper.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "discretize_curve.h"
#include "box.h"
#include "thread.h"
#include <vector>

template<class T, class N = std::complex<T>>
class FillMatrixBlock : public mt::Runnable{
public:
  FillMatrixBlock(Matrix<N>& matr,
      size_t i, size_t j, const DiscretizeCurve<T>& c1,
      const DiscretizeCurve<T>& c2, T waveNumber);
  void run() override;

private:
  Matrix<N>& matr;
  size_t i;
  size_t j;
  const DiscretizeCurve<T>& c1;
  const DiscretizeCurve<T>& c2;
  T waveNumber;
};

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
  std::vector<mt::Thread*> threads(sqr(curves.size()));
  Matrix<N> *matrix = new Matrix<N>(size);
  size_t startI = 0;
  for (size_t m = 0; m < curves.size(); m++) {
    size_t startJ = 0;
    for (size_t n = 0; n < curves.size(); n++) {
      threads[m * curves.size() + n] = new mt::Thread(
          *(new FillMatrixBlock<double>(*matrix, startI, startJ,
          curves[m], curves[n], waveNumber)));

      startJ += curves[n].size();
    }
    startI += curves[m].size();
  }
  for (auto i : threads){
    i->start();
  }
  delete threads.back();
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
void FillMatrixBlock<T, N>::run()
{
  if (i != j) {
    //not diagonal blocks
    for (size_t ii = 0; ii < c1.size(); ii++) {
      for (size_t jj = 0; jj < c2.size(); jj++) {
        matr[i + ii][j + jj] = (M_PI / c2.size())
            * h2(waveNumber * dist(c1[ii], c2[jj]));
      }
    }
  } else {
    //diagonal block
    for (size_t ii = 0; ii < c1.size(); ii++) {
      for (size_t jj = 0; jj < c1.size(); jj++) {
        N temp =
            ii != jj ?
                h2(waveNumber * dist(c1[ii], c2[jj]))
                    - epol::asymp(c1[ii].t, c1[jj].t) :
                epol::lim(c1[ii].d, waveNumber);
        matr[i + ii][j + jj] = (M_PI / c1.size())
            * (temp - N(0, 2) * epol::Ln(c1[ii].t, c1[jj].t, c1.size()) / M_PI);
      }
    }
  }
}

template<class T, class N>
FillMatrixBlock<T, N>::FillMatrixBlock(Matrix<N>& m, size_t i, size_t j,
    const DiscretizeCurve<T>& c1, const DiscretizeCurve<T>& c2,
    T waveNumber) : matr(m), i(i), j(j), c1(c1), c2(c2),
        waveNumber(waveNumber) {
}
#endif /* MT_DISCRETIZATION_H_ */
