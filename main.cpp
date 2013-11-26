#include <iostream>
#include "calc_manager.h"
#include "curve.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "box.h"
#include "helper.h"

int main(int argc, char** argv)
{
  double k = 5 * M_PI;
  double alpha = 0;

  int curvesNumber = 1;

  if (argc > 1)
    curvesNumber = atoi(argv[1]);
  DonationBox<Curve> listCurves;
  for (int i = 0; i < curvesNumber; i++)
    listCurves << new Line( { -1 + 2 * i, 4 }, { 0 + 2 * i, 3 });

  BlackBox<Curve> curvesSimple(listCurves);

  EPolarizationField field(k, alpha);
  IncidentFieldPackage fields(k);
  fields.addIncidentField(field);

  Given given(k, listCurves, fields);

  switch (argc) {
  case 5:
  case 4:
  case 3:
    given.points = atoi(argv[2]);
  }

  CalcManager cm(given);
  cm.run();
}
