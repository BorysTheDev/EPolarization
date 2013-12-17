#include <iostream>
#include <fstream>
#include "calc_manager.h"
#include "curve.h"
#include "incident_field.h"
#include "json_ui.h"

#include<QFile>
#include<QDebug>
#include <QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>

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
  //qWarning() << val;

  CalcManager cm(JsonUI::jsonToTask(val.toUtf8())[0]);
  cm.run();
}
