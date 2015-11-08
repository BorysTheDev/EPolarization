#ifndef HANKEL_H_
#define HANKEL_H_

#include <cmath>
#include <complex>

namespace mth {

//2nd kind Hankel 0 function
template<class T, class Complex = std::complex<T>>
Complex h2(const T& x)
{
  return Complex(_j0(x), -_y0(x));
}

template<class T, class Complex = std::complex<T>>
Complex h2(const int n, const T& x)
{
  return Complex(_jn(n, x), -_yn(n, x));
}

}

#endif /* HANKEL_H_ */
