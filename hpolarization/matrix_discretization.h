#ifndef MATRIX_DISCRETIZATION_H_
#define MATRIX_DISCRETIZATION_H_
#include <iostream>
#include <vector>
#include <memory>
#include "discretize_curve.h"
#include "chebyshev.h"
#include "h_core.h"
#include <iostream>
#include "hankel.h"

namespace hpl {

template<class Matrix>
Matrix& discretize(std::vector<crv::CurveForDiscretize> cs, Matrix& matr,
    int size)
{
  std::vector<crv::DiscretizeCurve> curves;
  for (auto& c : cs)
    curves.emplace_back(c, mth::uchebNodes<double>);

  //int i = leftBorderOf(ci1);
  //int j = leftBorderOf(ci2);
  const crv::DiscretizeCurve& c1 = curves[0];
  const crv::DiscretizeCurve& c2 = curves[0];

  //for (size_t ii = 0; ii < c1.size(); ii++, i++){
    for (size_t jj = 0; jj < c2.size(); jj++){
      matr[0][jj] = smoothCore(c1[0], c2[jj], 1);
      std::cout << matr[0][jj] << std::endl;
    }


      return matr;
}

}

#endif /* MATRIX_DISCRETIZATION_H_ */
