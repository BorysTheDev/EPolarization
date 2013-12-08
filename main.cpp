#include <iostream>
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
  double k = 5 * M_PI;
  double alpha = 0;
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
  qWarning() << val;

  QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
  QJsonObject sett2 = d.object();
  QJsonValue value = sett2.value(QString("appName"));
  qWarning() << value;
  QJsonObject item = value.toObject();
  qWarning() << ("QJsonObject of description: ") << item;

  /* incase of string value get value and convert into string*/
  qWarning() << ("QJsonObject[appName] of description: ") << item["description"];
  QJsonValue subobj = item["description"];
  qWarning() << subobj.toString();

  /* incase of array get array and convert into string*/
  qWarning() << ("QJsonObject[appName] of value: ") << item["imp"];
  QJsonArray test = item["imp"].toArray();
  qWarning() << test[1].toString();





  //std::vector<crv::CurveForDiscretize> listCurves;
  //listCurves.emplace_back(crv::Line({-1, 4}, {1, 2}), 20);
  //listCurves.emplace_back(crv::Line({-1, 4}, {1, 2}), 20);
  //    << new Parabola(-1 ,1 , 0.5);

  std::vector<ProtoPtr<IncidentField> > fields;
  fields.push_back(new EPolarizationField(k, alpha));
  Given given(k, JsonUI::jsonToTask(val.toUtf8())[0].curves, fields);
  CalcManager cm(given);
  cm.run();
}
