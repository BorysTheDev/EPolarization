#ifndef HELPER_H_
#define HELPER_H_
#include <complex>
#include <math.h>
#include "array.h"
#include "matrix.h"



template<typename T>
using MatrixPtr = std::unique_ptr<Matrix<T>>;

template<typename T>
using CMatrix = Matrix<std::complex<T>>;
template<typename T>
using CMatrixPtr = std::unique_ptr<CMatrix<T>>;

typedef CMatrix<double> DCMatrix;
typedef std::unique_ptr<DCMatrix> DCMatrixPtr;

template<typename T>
using ArrayPtr = std::unique_ptr<Array<T>>;

template<typename T>
using CArray = Array<std::complex<T>>;
template<typename T>
using CArrayPtr = std::unique_ptr<CArray<T>>;

typedef CArray<double> DCArray;
typedef std::unique_ptr<DCArray> DCArrayPtr;

const double epsilant = 0.000001;


#endif /* HELPER_H_ */
