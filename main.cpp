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
#include "curve_package.h"
#include "timer.h"
//#include <complex>

int main() {
	const double k = 5 * M_PI;
	double alpha = 0;
	//const int n = round(k/M_PI) * 100;

	//Line<double> line({-1,0},{1,0});
	//Parabola<double>* parabola = new Parabola<double>(-1,1,1);
	//CurvePackage<double> curves;
	//curves.addCurve(*parabola);

	//Line<double> line2({-1, -1}, {1, 1});
	Line<double> line1({-1, 4},{1, 2});
	Parabola<double> line2(-1,1,0.5);
	CurvePackage<double> curves(2);
	curves.addCurve(line1);
	curves.addCurve(line2);


	EPolarizationField<double> field(k, alpha);
	IncidentFieldPackage<double> fields(k);
	fields.addIncidentField(field);

	Discretization<double> d(curves, fields);

	std::cout << "Vector x(t_i):" <<std::endl;

	EquationMatrixSolver<std::complex<double>> ems;

	d.createArray();
	Timer timer;
	timer.start();
	CArrayPtr<double> x = ems(*d.createMatrix(), *d.createArray());
	timer.stop();
	std::cout << "calculation time:" <<std::endl;
	std::cout << timer.interval()<<std::endl;

	for (size_t i = 0; i < x->size(); i++) {
		std::cout << (*x)[i] << std::endl;
	}

	return 0;
}
