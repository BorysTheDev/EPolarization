#ifndef EQUATION_MATRIX_SOLVER_H_
#define EQUATION_MATRIX_SOLVER_H_

#include "helper.h"
#include "matrix.h"
#include "array.h"
#include <complex>

template<typename N>
class EquationMatrixSolver {
public:
	ArrayPtr<N> operator()(Matrix<N> matrix, const Array<N> f){
		LU(matrix);
		return reverseStroke(matrix, f);
	}
protected:
	void LU(Matrix<N>& luMatrix);
	ArrayPtr<N> reverseStroke(Matrix<N>& luMatrix, const Array<N>& f);

};

template<typename N>
void EquationMatrixSolver<N>::LU(Matrix<N>& luMatrix) {
	for (size_t i = 1; i < luMatrix.height(); i++)
		luMatrix[i][0] /= luMatrix[0][0];

	for (size_t i = 1; i < luMatrix.height(); i++) {
		for (size_t k = 0; k < i; k++)
			for (size_t j = i; j < luMatrix.height(); j++)
				luMatrix[i][j] -= luMatrix[i][k] * luMatrix[k][j];

		for (size_t j = i + 1; j < luMatrix.height(); j++) {
			N sum = 0;
			for (size_t k = 0; k < i; k++)
				sum += luMatrix[j][k] * luMatrix[k][i];
			luMatrix[j][i] = (luMatrix[j][i] - sum) / luMatrix[i][i];
		}
	}
}

template<typename N>
ArrayPtr<N> EquationMatrixSolver<N>::reverseStroke(Matrix<N>& luMatrix, const Array<N>& f) {
	//we don't want change f
	Array<N>* v = new Array<N>(f.size());
	for (size_t i = 0; i < f.size(); i++)
		(*v)[i] = f[i];
	// Lv=f
	for (size_t i = 1; i < f.size(); i++) {
		for (size_t j = 0; j < i; j++)
			(*v)[i] -= luMatrix[i][j] * (*v)[j];
	}
	// Ux=v
	for (long i = f.size() - 1; i >= 0; i--) {
		for (size_t j = i + 1; j < f.size(); j++)
			(*v)[i] -= luMatrix[i][j] * (*v)[j];
		(*v)[i] /= luMatrix[i][i];
	}
	return ArrayPtr<N>(v);
}

#endif /* EQUATION_MATRIX_SOLVER_H_ */
