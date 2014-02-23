#include "json_ui.h"
#include "curve.h"

#include <iostream>
#include <map>

#include <QJsonDocument>
#include <qjsonobject.h>
#include <QStringList>
#include <QJsonArray>

using namespace tps;

void JsonUI::updateGiven(const std::string str)
{
  QByteArray qba(str.c_str(),str.length());
  QJsonDocument doc = QJsonDocument::fromJson(qba);
  QJsonObject job = doc.object();
  jsonToLine(job["line"].toObject());
}

//Given JsonUI::getGiven()
//{
//  givenBuilder.getGiven();
//}

std::vector<Given> JsonUI::jsonToTask(const QByteArray& str)
{
  QJsonDocument doc = QJsonDocument::fromJson(str);
  //QJsonArray job = doc.object();
  std::vector<Given> tasks;
  tasks.push_back(jsonToTask(doc.object()["task1"].toObject()));
  return tasks;
}

Given JsonUI::jsonToTask(const QJsonObject& job)
{
  GivenBuilder gbuilder;
  for (auto& ob : job.keys()) {
    QJsonValue jov = job[ob];
    if (ob == "curves"){
      if (jov.isObject()) {
        for (auto curve : jov.toObject()){
          gbuilder.addCurve(jsonToCurve(curve));
        }
      } else {
        throw std::logic_error("json curves isn't an object");
      }
    } else if (ob == "fields") {
      if (jov.isObject()) {
        for (auto field : jov.toObject()){
          gbuilder.addField(jsonToIncField(field));
        }
      } else {
        throw std::logic_error("json field isn't an object");
      }
    } else {

    }
  }
  return gbuilder.getGiven();
}

crv::CurveForDiscretize JsonUI::jsonToCurve(const QJsonValue& job)
{
  typedef ProtoPtr<crv::Curve> (*toCurve)(const QJsonObject&);
  static std::map<QString, toCurve> curvesFuncs= {
    {"line", &jsonToLine}, {"userCurve", &jsonToUserCurve}
  };

  if (!job.isObject())
    throw std::logic_error("json curve isn't an object");
  QJsonObject curve = job.toObject();

  if (!curve["constructor"].isObject())
    throw std::logic_error("json curve constructor isn't an object");
  QJsonObject curveConstructor = curve["constructor"].toObject();

  try{
    return *curvesFuncs.at(curve["type"].toString())(curveConstructor);
  } catch(std::out_of_range) {
    throw std::logic_error(std::string("undefined curve type"));
  } catch(std::logic_error e) {
    throw std::logic_error(std::string("json curve error in ")
                           + e.what());
  }
}

ProtoPtr<crv::Curve> JsonUI::jsonToLine(const QJsonObject& job)
{
  try{
    return new crv::Line(jsonToPoint(job["a"].toObject()),
        jsonToPoint(job["b"].toObject()));
  } catch(std::logic_error e) {
    throw std::logic_error(std::string("json line error in ")
                           + e.what());
  }
}

ProtoPtr<crv::Curve> JsonUI::jsonToUserCurve(const QJsonObject& job)
{
  try{
    return new crv::UserCurve(job["x"].toString().toStdString(),
                              job["y"].toString().toStdString(),
                              job["dx"].toString().toStdString(),
                              job["dy"].toString().toStdString());
  } catch(std::logic_error e) {
    throw std::logic_error(std::string("json line error in ")
                           + e.what());
  }
}

ProtoPtr<IncidentField> JsonUI::jsonToIncField(const QJsonValue& job)
{
  typedef ProtoPtr<IncidentField> (*toField)(const QJsonObject&);
  static std::map<QString, toField> fieldsFuncs= {
    {"e_polarization", &jsonToEField}
  };

  if (!job.isObject())
    throw std::logic_error("json field isn't an object");
  QJsonObject field = job.toObject();

  if (!field["constructor"].isObject())
    throw std::logic_error("json field constructor isn't an object");
  QJsonObject fieldConstructor = field["constructor"].toObject();

  try{
    return fieldsFuncs.at(field["type"].toString())(fieldConstructor);
  } catch(std::out_of_range) {
    throw std::logic_error(std::string("undefined curve type"));
  } catch(std::logic_error e) {
    throw std::logic_error(std::string("json curve error in ")
                           + e.what());
  }
}

ProtoPtr<IncidentField> JsonUI::jsonToEField(const QJsonObject& job)
{
  try{
    return new EPolarizationField(jsonToReal(job["wavenumber"]),
        jsonToReal(job["alpha"]));
  } catch(std::logic_error e) {
    throw std::logic_error(std::string("json EField error in ")
                           + e.what());
  }
}

tps::RPoint JsonUI::jsonToPoint(const QJsonValue& job)
{
  if (!job.isObject())
    throw std::logic_error("json point isn't an object");
  try{
    return {jsonToReal(job.toObject()["x"]),
            jsonToReal(job.toObject()["y"])};
  } catch(std::logic_error e){
    throw std::logic_error(std::string("json point error in ")
                           + e.what());
  }
}

tps::real JsonUI::jsonToReal(const QJsonValue& job)
{
  if (!job.isDouble())
    throw std::logic_error("jsonValue isn't the real type");

  return job.toDouble();
}

/*
ProtoPtr<crv::Curve> JsonUI::createParabola(const QJsonObject& job)
{
  return new crv::Line({-1, 4}, {1, 2});
}
*/

