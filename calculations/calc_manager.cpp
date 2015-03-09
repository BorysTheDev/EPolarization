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
#include <fstream>
#include <locale>

template <class charT, charT sep>
class punct_facet: public std::numpunct<charT> {
protected:
    charT do_decimal_point() const { return sep; }
};

void CalcManager::run(){
	DonationBox<DiscretizeCurve> discCurves;
	for (size_t i = 0; i < given.curves.size(); i++)
		discCurves << new DiscretizeCurve(
		    given.curves[i], given.points, ch1Nodes);

	Discretization d(discCurves, given.fields);

	d.createArray();
	Timer timer;
	timer.start();
	auto matr = d.createMatrix(given.threads);
	auto x = d.createArray();
	timer.stop();
	std::cout << "fill matrix time:" << timer.interval()<<std::endl;
	timer.start();
	gaussMTBlockScheme(*matr, *x, matr->height(), given.threads, given.tileSize);
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
////////////////////////////////////////////////////
    int point_number = 1;
    std::ofstream current_out_re("current_re_1div2_40.csv");
    current_out_re.imbue(std::locale(current_out_re.getloc(), new punct_facet<char, ','>));
    for (int i = 0; i < currents.size(); i++)
    {
        for (int j = 0; j < currents[i].size(); j++)
        {
            current_out_re << point_number++ << ";";
        }
        current_out_re << std::endl;
        for (int j = 0; j < currents[i].size(); j++)
        {
            current_out_re << currents[i][j].real() << ";";
        }
        current_out_re << std::endl;
    }
   current_out_re.close();
//////////////////////////////////////////////////////
   point_number = 1;
   std::ofstream current_out_im("current_im_1div2_40.csv");
   current_out_im.imbue(std::locale(current_out_im.getloc(), new punct_facet<char, ','>));
   for (int i = 0; i < currents.size(); i++)
   {
       for (int j = 0; j < currents[i].size(); j++)
       {
           current_out_im << point_number++ << ";";
       }
       current_out_im << std::endl;
       for (int j = 0; j < currents[i].size(); j++)
       {
           current_out_im << currents[i][j].imag() << ";";
       }
       current_out_im << std::endl;
   }
   current_out_im.close();
/////////////////////////////////////////////////////////
    FieldSolver field_solver(discCurves, currents, given.wavenumber);

    std::ofstream field_out("field_1div2_40.csv");
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
