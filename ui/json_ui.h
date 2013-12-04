#ifndef UI_H_
#define UI_H_

#include "given.h"
#include "curve.h"
#include <string>
//#include <QJsonObject>

class JsonUI
{
public:
  void updateGiven(const std::string);
  //Given getGiven();

  //static Given toGiven(const std::string);

protected:
  //GivenBuilder givenBuilder;

  //ProtoPtr<crv::Curve> createLine(const QJsonObject&);
  //static ProtoPtr<crv::Curve> createParabola(const QJsonObject&);
};


#endif /* UI_H_ */
