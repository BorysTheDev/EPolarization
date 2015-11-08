#ifndef HELPER_H_
#define HELPER_H_
#include <math.h>
#include <utility>
#include "types.h"
#include "matrix.h"
/*
constexpr complex operator"" _i(long double v ) {
  return complex(0, v);
}

constexpr complex operator"" _i(unsigned long long v ) {
  return complex(0, v);
}*/

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


template<typename T>
using MatrixPtr = std::shared_ptr<Matrix<T>>;

template<typename T>
using CMatrix = Matrix<std::complex<T>>;
template<typename T>
using CMatrixPtr = std::shared_ptr<CMatrix<T>>;

typedef CMatrix<double> DCMatrix;
typedef std::shared_ptr<DCMatrix> DCMatrixPtr;

const double epsilant = 0.000001;

//1st kind Chebyshev polynom
template<class T = double>
T ch1(int n, const T& x) {
	return cos(n * acos(x));
}

//template<class T>
//T sqr(const T& base) {
//	return base * base;
//}

//1st kind Chebyshev nodes
double ch1Nodes(const int n, const int i);

//2nd kind Hankel function
//template<class T = double, class Complex = std::complex<T>>
//Complex h2(const T& x) {
//	return Complex(j0(x), -y0(x));
//}

template<class D>
auto sum(D data, int s, int e) -> decltype(std::declval<D>()(s)) {
	decltype(std::declval<D>()(s)) summ = 0;
	for (int i = s; i < e; i++)
		summ += data(i);
	return summ;
}


//all data for E-polarization wave
namespace epol {

//Euler-Mascheroni constant
const double gamma = 0.57721566490153286060651209008240243104215933593992;

/* limit
 * k - wave number
 * d- derivative
 */
types::complex lim(types::RPoint d, types::real k);

//ln(t0 - t_) integral
types::real Ln(const types::real& t0, const types::real& t_, const int n);

/* asymptotic for Hankel function
 *
 */
inline types::complex asymp(const types::real& t, const types::real& tau) {
	return -(types::complex(0, 2 * log(fabs(t - tau)) / M_PI));
}

}
#endif /* HELPER_H_ */
