#ifndef TEST_H_
#define TEST_H_

#include "chebyshev.h"
#include "types.h"
#include <type_traits>

template<class Matrix>
Matrix& discretize(Matrix& matr, int size)
{
  using namespace mth;
  int n = size + 1;
  typedef typename std::remove_const<
      typename std::remove_reference<decltype(matr[0][0])>::type>::type real;
  for (int i = 0; i < size; ++i) {
    for (int j = 0, j1 = 1; j < size; ++j, ++j1) {
      double temp = 0;
      for (int k = 0; k < size; ++k) {
        temp += (k + 1) * ucheb(k, uchebNodes<real>(n, j1))
            * ucheb(k, uchebNodes<real>(n, i + 1));
      }
      matr[i][j] = (-2.0 / n) * (1.0 - sqr(uchebNodes<real>(n, j1))) * temp;
    }
  }
  return matr;
}

#endif /* TEST_H_ */
