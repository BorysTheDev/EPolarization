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
#include "main_window.h"
#include <QtGui>
#include "given.h"
#include "calc_manager.h"
#include "thread.h"

using namespace mt;
//#include <complex>

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MainWindow mw;
	mw.show();

	double k = 5 * M_PI;
	double alpha = 0;

	DonationBox<Curve<double>> listCurves;
	listCurves << new Line<double>({-1, 4}, {1, 2})
			<< new Parabola<double>(-1 ,1 , 0.5);
	BlackBox<Curve<double>> curvesSimple(listCurves);

	EPolarizationField<double> field(k, alpha);
	IncidentFieldPackage<double> fields(k);
	fields.addIncidentField(field);

	Params given(k, listCurves, fields);
	CalcManager<double> cm(given);
	Thread t(cm);
	t.start();


	return app.exec();
}
