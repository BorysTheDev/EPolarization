#include <iostream>
#include "helper.h"
#include "equation_matrix_solver.h"
#include <memory>
#include "matrix.h"
#include "array.h"
#include "curve.h"
#include "incident_field.h"
#include <vector>
#include "discretization.h"
//#include <complex>

int main() {
	const double k = M_PI;
	double alpha = M_PI / 2;
	const int n = 10;//round(k/M_PI) * 10;

	Curve<double> curve;
	std::vector<Curve<double>*> curves;
	curves.push_back(&curve);

	EPolarizationField<double> field(k, alpha);
	IncidentFieldPackage<double> fields(1, k);
	fields.setIncidentField(0, field);

	Discretization<double> d(curves, fields);
	EquationMatrixSolver<double> ems;

	d.createArray();
	std::shared_ptr<Array<std::complex<double>>> x = ems(d.createMatrix(), d.createArray());

	for (int i = 0; i < n; i++) {
		std::cout << (*x)[i] << std::endl;
	}


	return 0;
}
