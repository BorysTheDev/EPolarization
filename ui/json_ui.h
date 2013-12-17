#ifndef UI_H_
#define UI_H_

#include "given.h"
#include "curve.h"
#include <string>
#include <QJsonObject>
#include "discretize_curve.h"

class JsonUI
{
public:
  void updateGiven(const std::string);
  //Given getGiven();

  static std::vector<Given> jsonToTask(const QByteArray&);

protected:
  //GivenBuilder givenBuilder;
  static Given jsonToTask(const QJsonObject&);
  static crv::CurveForDiscretize jsonToCurve(const QJsonValue&);
  static ProtoPtr<IncidentField> jsonToIncField(const QJsonValue&);
  static ProtoPtr<IncidentField> jsonToEField(const QJsonObject&);

  static ProtoPtr<crv::Curve> jsonToLine(const QJsonObject&);
  static tps::RPoint jsonToPoint(const QJsonValue&);
  static tps::real jsonToReal(const QJsonValue&);

  const char* params = "params";
  const char* type = "type";
  const char* curves = "curves";
  const char* fields = "fields";

  //static ProtoPtr<crv::Curve> createParabola(const QJsonObject&);
};


#endif /* UI_H_ */
