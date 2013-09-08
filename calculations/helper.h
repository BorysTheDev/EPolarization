#ifndef HELPER_H_
#define HELPER_H_
#include <math.h>
#include "array.h"
#include "matrix.h"
#include <utility>
#include "types.h"

constexpr complex operator"" _i(long double v ) {
  return complex(0, v);
}

constexpr complex operator"" _i(unsigned long long v ) {
  return complex(0, v);
}

template<typename T>
using MatrixPtr = std::shared_ptr<Matrix<T>>;

template<typename T>
using CMatrix = Matrix<std::complex<T>>;
template<typename T>
using CMatrixPtr = std::shared_ptr<CMatrix<T>>;

typedef CMatrix<double> DCMatrix;
typedef std::shared_ptr<DCMatrix> DCMatrixPtr;

template<typename T>
using ArrayPtr = std::shared_ptr<Array<T>>;

template<typename T>
using CArray = Array<std::complex<T>>;
template<typename T>
using CArrayPtr = std::shared_ptr<CArray<T>>;

typedef CArray<double> DCArray;
typedef std::shared_ptr<DCArray> DCArrayPtr;

const double epsilant = 0.000001;

//1st kind Chebyshev polynom
template<class T = double>
T ch1(int n, const T& x) {
	return cos(n * acos(x));
}

template<class T>
T sqr(const T& base) {
	return base * base;
}

//1st kind Chebyshev nodes
double ch1Nodes(const int n, const int i) {
	return cos((2.0 * i + 1.0) * M_PI / (2.0 * n));
}

//2nd kind Hankel function
template<class T = double, class Complex = std::complex<T>>
Complex h2(const T& x) {
	return Complex(j0(x), -y0(x));
}

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
complex lim(Point<real> d, real k) {
	return -complex(0, 2 / M_PI)
			* (log(k * sqrt(sqr(d.x) + sqr(d.y)) / 2) - M_PI / complex(0, 2) + gamma);
}

//ln(t0 - t_) integral
real Ln(const real& t0, real const& t_, const int n) {
	double sum = 0;
	for (int p = 1; p < n; p++) {
		sum += ch1(p, t_) * ch1(p, t0) / p;
	}
	return -(log(2) + 2 * sum);
}

/* asymptotic for Hankel function
 *
 */
inline complex asymp(const real& t, const real& tau) {
	return -(complex(0, 2 * log(fabs(t - tau)) / M_PI));
}

}
#endif /* HELPER_H_ */
