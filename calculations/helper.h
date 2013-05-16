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
T ch1(int n, const T& x){
	return cos(n * acos(x));
}

template<class T>
T sqr(const T& base){
	return base * base;
}

//1st kind Chebyshev nodes
double ch1Nodes(const int n, const int i){
	return cos((2.0 * i + 1.0) * M_PI / (2.0 * n));
}

//2nd kind Hankel function
template<class T = double, class Complex = std::complex<T>>
Complex h2(const T& x) {
	return Complex(j0(x),-y0(x));
}

#endif /* HELPER_H_ */
