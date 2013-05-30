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
#include "box.h"
#include "discretize_curve.h"
#include "field_solver.h"
//#include <complex>

int main() {
	const double k = 5 * M_PI;
	double alpha = 0;

	DonationBox<Curve<double>> listCurves;
	listCurves << new Line<double>({-1, 4}, {1, 2})
			<< new Parabola<double>(-1 ,1 , 0.5);
	BlackBox<Curve<double>> curvesSimple(listCurves);

	EPolarizationField<double> field(k, alpha);
	IncidentFieldPackage<double> fields(k);
	fields.addIncidentField(field);

	DonationBox<DiscretizeCurve<double>> discCurves;
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

	DonationBox<Array<std::complex<double>>> currents;
	size_t p = 0;
	for (size_t i = 0; i < discCurves.size(); i++) {
		Array<std::complex<double>>* current =
				new Array<std::complex<double>>(discCurves[i].size());
		for (size_t j = 0; j < discCurves[i].size(); j++, p++) {
			(*current)[j] = (*x)[p];
		}
		currents << current;
	}

	FieldSolver<double> f(discCurves, currents, k);
	std::cout <<std::endl<<std::endl<< f(2,2)<<std::endl ;
	return 0;
}
