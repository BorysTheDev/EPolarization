#include <iostream>
#include "calc_manager.h"
#include "curve.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "box.h"
#include "helper.h"


int main(int argc, char** argv) {
  double k = 4 * M_PI;
  double alpha = 0;

  int curvesNumber = 7;


  if (argc > 1) curvesNumber = atoi(argv[1]);
  DonationBox<Curve> listCurves;
  for (int i = 0; i < curvesNumber; i++)
  {
    listCurves << new Line({-1 / 7, 0.5 + 1.5 * i}, {-8 / 7, 0.5 + 1.5 * i});
  }
  for (int i = 0; i < curvesNumber; i++)
  {
    listCurves << new Line({0, 0 + 1.5 * i}, {0, 1 + 1.5 * i});
  }
  for (int i = 0; i < curvesNumber - 1; i++)
  {
    listCurves << new Line({1 / 7, 1.25 + 1.5 * i}, {8 / 7, 1.25 + 1.5 * i});
  }

  BlackBox<Curve> curvesSimple(listCurves);

  EPolarizationField field(k, alpha);
  IncidentFieldPackage fields(k);
  fields.addIncidentField(field);

  Given given(k, listCurves, fields);
    switch (argc) {
    case 5:
      given.tileSize = atoi(argv[4]);
    case 4:
      given.threads = atoi(argv[3]);
    case 3:
      given.points = atoi(argv[2]);
    }
  given.points = 40;

  CalcManager cm(given);
  cm.run();
}
