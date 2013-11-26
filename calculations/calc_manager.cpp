#include "calc_manager.h"
#include <iostream>
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
#include "gauss.h"


void CalcManager::run(){
	DonationBox<DiscretizeCurve> discCurves;
	for (size_t i = 0; i < given.curves.size(); i++)
		discCurves << new DiscretizeCurve(
		    given.curves[i], given.points, ch1Nodes);

	Discretization d(discCurves, given.fields);

	d.createArray();
	Timer timer;
	timer.start();
	auto matr = d.createMatrix();
	auto x = d.createArray();
	timer.stop();
	std::cout << "fill matrix time:" << timer.interval()<<std::endl;
	timer.start();
	gaussScheme(*matr, *x, matr->height());
	timer.stop();
	std::cout << "SLAE time:" << timer.interval()<<std::endl;

	timer.start();
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

	FieldSolver f(discCurves, currents, given.wavenumber);
	for (int i = 0; i < 180; i++){
				f.farField(i);
	}
	timer.stop();
	std::cout << "far field time:" << timer.interval()<<std::endl;
	std::cout <<std::endl<<std::endl<< f.field({2,2})<<std::endl
			<<std::endl<< f.farField(1);
}
