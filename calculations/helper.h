#ifndef HELPER_H_
#define HELPER_H_
#include <complex>
#include <math.h>
#include "array.h"
#include "matrix.h"

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

//all data for E-polarization wave
namespace epol {

//Euler–Mascheroni constant
const double gamma = 0.57721566490153286060651209008240243104215933593992;

/* limit
 * k - wave number
 */
template<class T, class N = std::complex<T>>
N lim(T dx, T dy, T k) {
	return -N(0, 2 / M_PI)
			* (log(k * sqrt(sqr(dx) + sqr(dy)) / 2) - M_PI / N(0, 2) + gamma);
}

//ln(t0 - t_) integral
template<class T>
T Ln(const T& t0, T const& t_, const int n) {
	double sum = 0;
	for (int p = 1; p < n; p++) {
		sum += ch1(p, t_) * ch1(p, t0) / p;
	}
	return -(log(2) + 2 * sum);
}

/* asymptotic for Hankel function
 *
 */
template<class T, class N = std::complex<T>>
inline N asymp(const T& t, const T& tau) {
	return -(N(0, 2 * log(fabs(t - tau)) / M_PI));
}

/* kernel for E-polarization equation
 * k - wave number
 */
template<class T, class N = std::complex<T>>
inline N kernel(const T& x1, const T& x2, const T& y1, const T &y2,
		const T& k) {
	return h2(k * sqrt(sqr(x1 - y1) + sqr(x2 - y2)));
}
}
#endif /* HELPER_H_ */
