#include "calc_manager.h"
#include <iostream>
#include <fstream>
#include <locale>
#include "array.h"
#include "curve.h"
#include "incident_field.h"
#include <vector>
#include "discretization.h"
#include "timer.h"
#include "box.h"
#include "discretize_curve.h"
#include "field_solver.h"
#include "gauss.h"

template <class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
protected:
    charT do_decimal_point() const { return sep; }
};

void CalcManager::run(){
	DonationBox<crv::DiscretizeCurve> discCurves;
	for (size_t i = 0; i < given.curves.size(); i++)
		discCurves << new crv::DiscretizeCurve(
		    given.curves[i], ch1Nodes);

	Discretization d(discCurves, given.fields);

	std::cout << "Vector x(t_i):" <<std::endl;

	d.createArray();
	Timer timer;
	timer.start();
	auto matr = d.createMatrix();
	auto x = d.createArray();
	timer.stop();
	std::cout << "fill matrix time:" << timer.interval()<<std::endl;
	timer.start();
	gaussBlockScheme(*matr, *x, matr->height(), 30);
	timer.stop();
	std::cout << "calculation time:" << timer.interval()<<std::endl;

	for (size_t i = 0; i < x->size(); i++) {
    //std::cout << (*x)[i] << std::endl;
	}
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
  std::ofstream fout("result.csv");
  for (int i = 0; i < 360; i+=1)
    fout << i<< ";";
  fout <<std::endl;
  fout.imbue(std::locale(fout.getloc(), new punct_facet<char, ','>));
  for (int i = 0; i < 360; i+=1){
    //std::cout <<std::endl<<f.farField(i);

    fout << std::abs(f.farField(i*M_PI/180))<< ";";
	}
  fout.close();
	timer.stop();
	std::cout << "far field time:" << timer.interval()<<std::endl;
	std::cout <<std::endl<<std::endl<< f.field({2,2})<<std::endl
			<<std::endl<< f.farField(1);
}
