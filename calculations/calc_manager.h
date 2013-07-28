#ifndef CALC_MANAGER_H_
#define CALC_MANAGER_H_

#include "given.h"
#include <iostream>
#include "equation_matrix_solver.h"
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
#include "thread.h"


template<class T>
class CalcManager : public mt::Runnable{
public:
	CalcManager(Given<T>);

	void run() override;

private:
	Given<T> given;
};

template<class T>
CalcManager<T>::CalcManager(Given<T> params):given(params){
}

template<class T>
void CalcManager<T>::run(){
	DonationBox<DiscretizeCurve<double>> discCurves;
	for (size_t i = 0; i < given.curves.size(); i++)
		discCurves << new DiscretizeCurve<double>(given.curves[i], (i + 1) * 10, ch1Nodes);

	Discretization<double> d(discCurves, given.fields);

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

	FieldSolver<double> f(discCurves, currents, given.wavenumber);
	std::cout <<std::endl<<std::endl<< f({2,2})<<std::endl ;
}

#endif /* CALC_MANAGER_H_ */
