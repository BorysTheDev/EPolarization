#include "json_ui.h"
#include "curve.h"

#include <iostream>

#include <QJsonDocument>
#include <qjsonobject.h>

void JsonUI::updateGiven(const std::string str)
{
 //QJsonDocument doc = QJsonDocument::fromJson(
  //    QByteArray().append(QString::fromStdString(str)));
//  std::cout << "test"  << std::endl;
//  QJsonObject job = (doc.object());
//  std::cout << "test" << job["a"].toDouble() << std::endl;
}

//Given JsonUI::getGiven()
//{
//  givenBuilder.getGiven();
//}

//Given JsonUI::toGiven(const std::string)
//{
//  return Given();
//}

//ProtoPtr<crv::Curve> JsonUI::createLine(const QJsonObject& job)
//{
//  std::cout << "test" << job["a"].toDouble() << std::endl;
//  return new crv::Line({-1, 4}, {1, 2});
//}
/*
ProtoPtr<crv::Curve> JsonUI::createParabola(const QJsonObject& job)
{
  return new crv::Line({-1, 4}, {1, 2});
}
*/
