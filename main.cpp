#include <iostream>
#include "calc_manager.h"
#include "curve.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "box.h"
#include "helper.h"

int main(int argc, char** argv) {
  double k = 5 * M_PI;
  double alpha = 0;

  DonationBox<Curve> listCurves;
  listCurves << new Line({-1, 4}, {0, 3})
  <<new Line({-2, -1}, {-2, 1})
  <<new Line({0, -1}, {0, 1})
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

  Given given(k, listCurves, fields);
  switch (argc)
    {
    case 4:
      given.tileSize = atoi(argv[3]);
    case 3:
      given.threads =  atoi(argv[2]);
    case 2:
         given.points =  atoi(argv[1]);
    }
  CalcManager cm(given);
  cm.run();
}
