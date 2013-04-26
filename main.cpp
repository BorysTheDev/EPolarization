#include <iostream>
#include "helper.h"

#include <complex>
int main() {
	const int n = 10;
	complex** matrix = new complex*[n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new complex[n];
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (PI / n)
					* (K(t_(n, i), t_(n, j))
							+ complex(0, 2 * Ln(t_(n, i), t_(n, j), n) / PI));
		}

	}
	complex* f = new complex[n];
	for (int i = 0; i < n; i++) {
		f[i] = complex(0, 2) * u0(t_(n, i));
	}

	simpleLU(matrix, n);
	complex* x = reverseStroke(matrix, f, n);
	for (int i = 0; i < n; i++) {
		std::cout << x[i] << std::endl;
	}

	delete[] x;
	delete[] f;
	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;

	return 0;
}
