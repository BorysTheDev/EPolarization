#include <iostream>
#include "calc_manager.h"
#include "curve.h"
#include "incident_field.h"
#include "json_ui.h"

#include <qbytearray.h>

int main(int argc, char** argv) {
  std::cout << "test"  << std::endl;

  QByteArray();
  double k = 5 * M_PI;
  double alpha = 0;
  std::string param;
  Given given;

  //JsonUI jui;
  //jui.updateGiven("{\"a\":\"985\"}");
  //while (true)
  {
    std::cout << "test"  << std::endl;
    //std::cin >> param;



  }





  /*std::vector<crv::CurveForDiscretize> listCurves;
  listCurves.emplace_back(crv::Line({-1, 4}, {1, 2}), 20)
      << new Parabola(-1 ,1 , 0.5);

  std::vector<ProtoPtr<IncidentField> > fields;
  fields.push_back(new EPolarizationField(k, alpha));

  Given given(k, listCurves, fields);
  CalcManager cm(given);
  cm.run();*/
}
