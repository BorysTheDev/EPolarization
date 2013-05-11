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
#include "incident_field_package.h"
#include "timer.h"
//#include <complex>

int main() {
	const double k = M_PI * 10;
	double alpha = 3*M_PI / 2;
	//const int n = round(k/M_PI) * 100;

	Line<double> line({-1,0},{1,0});
	std::vector<Curve<double>*> curves;
	curves.push_back(&line);

	EPolarizationField<double> field(k, alpha);
	IncidentFieldPackage<double> fields(k);
	fields.addIncidentField(field);

	Discretization<double> d(curves, fields);
	EquationMatrixSolver<std::complex<double>> ems;

	d.createArray();
	Timer timer;
	timer.start();
	CArrayPtr<double> x = ems(*d.createMatrix(), *d.createArray());
	timer.stop();
	std::cout << timer.interval()<<std::endl;

	for (size_t i = 0; i < x->size(); i++) {
		std::cout << (*x)[i] << std::endl;
	}


	return 0;
}
