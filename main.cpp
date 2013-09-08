#include <iostream>
#include "given.h"
#include "calc_manager.h"
#include "curve.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "box.h"
#include "thread.h"

int main(int argc, char** argv) {
  double k = 5 * M_PI;
  double alpha = 0;

  DonationBox<Curve> listCurves;
  listCurves << new Line({-1, 4}, {1, 2})
      << new Parabola(-1 ,1 , 0.5)
      << new Line({2, 4}, {3, 2})
      << new Line({4, 4}, {5, 2})
      << new Line({4, 5}, {5, 3})
      << new Line({4, 6}, {5, 4})
      << new Line({4, 7}, {5, 5})
      << new Line({4, 8}, {5, 6})
      << new Line({2, 5}, {4, 7});
  BlackBox<Curve> curvesSimple(listCurves);

  EPolarizationField field(k, alpha);
  IncidentFieldPackage fields(k);
  fields.addIncidentField(field);

  Params given(k, listCurves, fields);
  CalcManager<double> cm(given);
  cm.run();
}
