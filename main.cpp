#include <iostream>
#include "calc_manager.h"
#include "curve.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "helper.h"
#include "ellipse.h"
#include "cubic_spline.h"

int main(int argc, char** argv) {
  double k = M_PI;
  double alpha = 0;

  int curvesNumber = 7;


  if (argc > 1) curvesNumber = atoi(argv[1]);
  std::vector<Curve::Ptr> listCurves;
//  for (int i = 0; i < curvesNumber; i++)
//  {
//    listCurves.emplace_back( new Line({-1.0 / 7.0, 0.5 + 1.5 * i}, {-8.0 / 7.0, 0.5 + 1.5 * i}) );
//  }
//  for (int i = 0; i < curvesNumber; i++)
//  {
//    listCurves.emplace_back( new Line({0.0, 0 + 1.5 * i}, {0.0, 1 + 1.5 * i}) );
//  }
//  for (int i = 0; i < curvesNumber - 1; i++)
//  {
//    listCurves.emplace_back( new Line({1.0 / 7.0, 1.25 + 1.5 * i}, {8.0 / 7.0, 1.25 + 1.5 * i}) );
//  }

  listCurves.emplace_back( new CubicSpline() );
  EPolarizationField field(k, alpha);
  IncidentFieldPackage fields(k);
  fields.addIncidentField(field);

  Given given(k, std::move(listCurves), fields);
    switch (argc) {
    case 5:
      given.tileSize = atoi(argv[4]);
    case 4:
      given.threads = atoi(argv[3]);
    case 3:
      given.points = atoi(argv[2]);
    }
  given.points = 1001; //need to be always odd

  CalcManager cm(std::move(given));
//  cm.run();
  cm.calcH();
}
