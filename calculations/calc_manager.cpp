#include "calc_manager.h"
#include <iostream>
#include "curve.h"
#include "incident_field.h"
#include <vector>
#include "discretization.h"
#include "incident_field_package.h"
#include "timer.h"
#include "discretize_curve.h"
#include "field_solver.h"
#include "gauss.h"
#include <fstream>
#include <locale>

template <class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
protected:
    charT do_decimal_point() const { return sep; }
};

void CalcManager::run(){
    std::vector<DiscretizeCurve::Ptr> discCurves;
	for (size_t i = 0; i < given.curves.size(); i++)
        discCurves.emplace_back( new DiscretizeCurve(
            *given.curves[i], given.points, ch1Nodes) );

	Discretization d(discCurves, given.fields);

	d.createArray();
	Timer timer;
	timer.start();
	auto matr = d.createMatrix(given.threads);
	auto x = d.createArray();
	timer.stop();
	std::cout << "fill matrix time:" << timer.interval()<<std::endl;
	timer.start();
    gaussMTBlockScheme(*matr, x, matr->height(), given.threads, given.tileSize);
	timer.stop();
	std::cout << "SLAE time:" << timer.interval()<<std::endl;

	timer.start();
    std::vector<std::vector<std::complex<double>>> currents;
	size_t p = 0;
	for (size_t i = 0; i < discCurves.size(); i++) {
        std::vector<std::complex<double>> current(discCurves[i]->size());
        for (size_t j = 0; j < discCurves[i]->size(); j++, p++) {
            current[j] = x[p];
		}
        currents.emplace_back(std::move(current));
    }
////////////////////////////////////////////////////
    std::ofstream current_out_re("current_re_1div7_140.csv");
    current_out_re.imbue(std::locale(current_out_re.getloc(), new punct_facet<char, ','>));
    for (size_t i = 0; i < currents.size(); i++)
    {
        for (size_t j = 0; j < currents[i].size(); j++)
        {
            current_out_re << (*discCurves[i])[j].t << ";";
        }
        current_out_re << std::endl;
        for (size_t j = 0; j < currents[i].size(); j++)
        {
            auto val = currents[i][j] / sqrt(1 - sqr((*discCurves[i])[j].t));
            current_out_re << val.real() << ";";
        }
        current_out_re << std::endl;
    }
   current_out_re.close();
//////////////////////////////////////////////////////

   std::ofstream current_out_im("current_im_1div7_140.csv");
   current_out_im.imbue(std::locale(current_out_im.getloc(), new punct_facet<char, ','>));
   for (size_t i = 0; i < currents.size(); i++)
   {
       for (size_t j = 0; j < currents[i].size(); j++)
       {
           current_out_im << (*discCurves[i])[j].t << ";";
       }
       current_out_im << std::endl;
       for (size_t j = 0; j < currents[i].size(); j++)
       {
           auto val = currents[i][j] / sqrt(1 - sqr((*discCurves[i])[j].t));
           current_out_im << val.imag() << ";";
       }
       current_out_im << std::endl;
   }
   current_out_im.close();
/////////////////////////////////////////////////////////
    FieldSolver field_solver(discCurves, currents, given.wavenumber);

    std::ofstream field_out("field_1div7_140.csv");
    for (int i = 0; i < 360; i+=1)
    {
        field_out << i<< ";";
    }
    field_out << std::endl;
    field_out.imbue(std::locale(field_out.getloc(), new punct_facet<char, ','>));
    for (int i = 0; i < 360; i+=1)
    {
        field_out << std::abs(field_solver.farField(i*M_PI/180))<< ";";
    }
    field_out.close();

	timer.stop();
	std::cout << "far field time:" << timer.interval()<<std::endl;
    std::cout <<std::endl<<std::endl<< field_solver.field({2,2})<<std::endl
            <<std::endl<< field_solver.farField(1);
}
