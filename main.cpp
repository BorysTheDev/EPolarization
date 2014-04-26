#include <iostream>
#include <fstream>
#include "calc_manager.h"
#include "curve.h"
#include "incident_field.h"
#include "json_ui.h"

#include<QFile>
#include<QDebug>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>
#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/json_parser.hpp>

int main(int argc, char** argv) {
  //double k = 2 * M_PI / 3;
  //double alpha = M_PI / 2;
  std::string param;
  //Given given;

  JsonUI jui;
  jui.updateGiven("{\"line\":{\"a\":{\"x\":-1,\"y\":4},"
                             "\"b\":{\"x\":1,\"y\":2}}}");

  QString val;
  QFile file;
  file.setFileName("test.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  val = file.readAll();
  file.close();
  boost::property_tree::ptree json_tree;
  boost::property_tree::read_json("test.json", json_tree);
  //qWarning() << val;

  CalcManager cm1(JsonUI::jsonToTask(val.toUtf8())[0]);
  CalcManager cm2(JsonUI::jsonToTask(json_tree)[0]);
  std::cout<<"String:"<<std::endl;
  cm1.run();
  std::cout<<std::endl<<std::endl;
  std::cout<<"Property_Tree:"<<std::endl;
  cm2.run();
}
