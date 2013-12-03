#include <iostream>
#include "calc_manager.h"
#include "curve.h"
#include "incident_field.h"
#include "helper.h"

int main(int argc, char** argv) {
  double k = 5 * M_PI;
  double alpha = 0;

  std::vector<crv::CurveForDiscretize> listCurves;
  listCurves.emplace_back(crv::Line({-1, 4}, {1, 2}), 20);
      /*<< new Parabola(-1 ,1 , 0.5)
      << new Line({2, 4}, {3, 2})
      << new Line({4, 4}, {5, 2})
      << new Line({4, 5}, {5, 3})
      << new Line({4, 6}, {5, 4})
      << new Line({4, 7}, {5, 5})
      << new Line({4, 8}, {5, 6})
      << new Line({2, 5}, {4, 7})*/;

  std::vector<ProtoPtr<IncidentField> > fields;
  fields.push_back(new EPolarizationField(k, alpha));

  Given given(k, listCurves, fields);
  CalcManager cm(given);
  cm.run();
}
