#include "main_window.h"
#include <iostream>
#include "given.h"
#include "calc_manager.h"
#include "curve.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "box.h"
#include "thread.h"

using namespace mt;

MainWindow::MainWindow() {
	calcBtn = new QPushButton(this);
	connect(calcBtn, SIGNAL(clicked(bool)), SLOT(calculate()));
}

void MainWindow::calculate(){
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
}
