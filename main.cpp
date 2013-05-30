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
#include "box.h"
#include "discretize_curve.h"
//#include <complex>

int main() {
	const double k = 5 * M_PI;
	double alpha = 0;
	//const int n = round(k/M_PI) * 100;

	DonationBox<Curve<double>> listCurves;
	listCurves << new Line<double>({-1, 4}, {1, 2})
			<< new Parabola<double>(-1 ,1 , 0.5);
	BlackBox<Curve<double>> curvesSimple(listCurves);

	EPolarizationField<double> field(k, alpha);
	IncidentFieldPackage<double> fields(k);
	fields.addIncidentField(field);

	DonationBox<DiscretizeCurve<double>> discCurves;
	//int discSize = round(k / M_PI) * 2;
	for (size_t i = 0; i < curvesSimple.size(); i++)
		discCurves << new DiscretizeCurve<double>(curvesSimple[i], (i + 1) * 10, ch1Nodes);

	//BlackBox<DiscretizeCurve<double>> curves(discCurves);
	Discretization<double> d(discCurves, fields);

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
