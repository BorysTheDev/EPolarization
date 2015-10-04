#ifndef CHEBYSHEV_H_
#define CHEBYSHEV_H_

#include <cmath>
#include "simple_math.h"

namespace mth {

//Chebyshev of the first kind.
template<class T>
T tcheb(int n, const T& x)
{
  return std::cos(n * std::acos(x));
}
//Chebyshev of the second kind.
template<class T>
T ucheb(int n, const T& x)
{
  T acx = std::acos(x);
  return std::sin((n + 1) * acx) / std::sin(acx);
}

//Chebyshev nodes of the first kind.
template<class T>
T tchebNodes(const int n, const int i)
{
  return std::cos(((2 * i + 1) * (T)M_PI) / (2 * n));
}

//Chebyshev nodes of the second kind.
template<class T>
T uchebNodes(const int n, const int i)
{
  return std::cos((i * (T)M_PI) / n);
}

}

#endif /* CHEBYSHEV_H_ */
