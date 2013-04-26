#ifndef HELPER_H_
#define HELPER_H_
#include <complex>
#include <cmath>


//Function names isn't good
typedef std::complex<double> complex;

const double PI = 3.1415926535897932384626433832795;
const double ALPHA = PI / 2;
const double k = 5 * PI;
const double epsilant = 0.000001;
double x(const double& t) {
	return t;
}

//don't use pow with integer variable, it's only example
double y(const double& t) {
	return pow(t, 2) / 2;
}

complex h1(const double& x) {
	return complex(j0(x), y0(x));
}

complex u0(const double& tau) {
	double expArg = (x(tau) * cos(ALPHA) - y(tau) * sin(ALPHA)) * k;
	return (-2.0) * exp(complex(0, expArg));
}

//don't use pow with integer power variable, it's only example
complex K(const double& t, const double& tau_) {
	double tau = t == tau_ ? tau_ + epsilant : tau_;
	double sqrtArg = pow(x(t) - x(tau), 2) + pow(y(t) - y(tau), 2);
	return h1(k * sqrt(sqrtArg)) - complex(0, 2 * log(fabs(t - tau)) / PI);
}

double chebyshevcalculate(int n, double x){
	return cos(n * acos(x));
}
double Ln(const double t0, double const t_,const int n) {
	double sum = 0;
	for (int p = 1; p < n; p++) {
		sum += chebyshevcalculate(p, t_) * chebyshevcalculate(p, t0) / p;
	}
	return -(log(2) + 2 * sum);
}

double t_(const int n, const int i){
	return cos((2.0 * i + 1.0) * PI / (2.0 * n));
}

template <typename N>
void simpleLU(N** luMatrix, int size) {
	for (int i = 1; i < size; i++)
		luMatrix[i][0] /= luMatrix[0][0];

	for (int i = 1; i < size; i++) {
		for (int k = 0; k < i; k++)
			for (int j = i; j < size; j++)
				luMatrix[i][j] -= luMatrix[i][k] * luMatrix[k][j];

		for (int j = i + 1; j < size; j++) {
			N sum = 0.0;
			for (int k = 0; k < i; k++)
				sum += luMatrix[j][k] * luMatrix[k][i];
			luMatrix[j][i] = (luMatrix[j][i] - sum) / luMatrix[i][i];
		}
	}
}

template <typename N>
N* reverseStroke(N** luMatrix, N* f, int size) {
	//we don't want change f
	N* v = new N[size];
	for (int i = 0; i < size; i++)
		v[i] = f[i];
	// Lv=f
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < i; j++)
			v[i] -= luMatrix[i][j] * v[j];
	}
	// Ux=v
	for (int i = size - 1; i >= 0; i--) {
		for (int j = i + 1; j < size; j++)
			v[i] -= luMatrix[i][j] * v[j];
		v[i] /= luMatrix[i][i];
	}
	return v;
}

#endif /* HELPER_H_ */
