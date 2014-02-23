#ifndef CURVE_H_
#define CURVE_H_
#include "point.h"
#include <cmath>
#include "types.h"
#include "prototype.h"
#include "equation_interpreter.h"
#include <string>

namespace crv
{

class Curve : public Prototype<Curve> {
public:
	virtual tps::real x(tps::real t) const = 0;
	virtual tps::real y(tps::real t) const = 0;
	virtual tps::real dx(tps::real t) const = 0;
	virtual tps::real dy(tps::real t) const = 0;
	virtual tps::real d2x(tps::real t) const = 0;
	virtual tps::real d2y(tps::real t) const = 0;

	virtual tps::real length() const = 0;

  virtual ~Curve(){}
};

class Line: public Curve {
public:
	Line(const tps::RPoint& a, const tps::RPoint& b);

	tps::real x(tps::real t) const override;
	tps::real y(tps::real t) const override;
	tps::real dx(tps::real t) const override {return cosPhi * len / 2;}
	tps::real dy(tps::real t) const override {return sinPhi * len / 2;}
  tps::real d2x(tps::real t) const override {return 0;}
  tps::real d2y(tps::real t) const override {return 0;}

	tps::real length() const override {return len;}

	ProtoPtr<Curve> clone() const override;

private:
  tps::RPoint p1;
  tps::RPoint p2;
  tps::real cosPhi;
  tps::real sinPhi;
  tps::real len;
};

class UserCurve: public Curve {
public:
  UserCurve(const std::string, const std::string, const std::string,
            const std::string, const std::string _d2x = "0",
            const std::string _d2y = "0");

  tps::real x(tps::real t) const override {return _x.solve({{'t',t}});}
  tps::real y(tps::real t) const override {return _y.solve({{'t',t}});}
  tps::real dx(tps::real t) const override {return _dx.solve({{'t',t}});}
  tps::real dy(tps::real t) const override {return _dy.solve({{'t',t}});}
  tps::real d2x(tps::real t) const override {return _d2x.solve({{'t',t}});}
  tps::real d2y(tps::real t) const override {return _d2y.solve({{'t',t}});}

  tps::real length() const override {return 1;}

  ProtoPtr<Curve> clone() const override;

private:
  std::string str_x;
  std::string str_y;
  std::string str_dx;
  std::string str_dy;
  std::string str_d2x;
  std::string str_d2y;

  EquationInterpreter _x;
  EquationInterpreter _y;
  EquationInterpreter _dx;
  EquationInterpreter _dy;
  EquationInterpreter _d2x;
  EquationInterpreter _d2y;
};

//TODO change derivative
class Parabola: public Curve {
public:
	Parabola(const tps::real& x1, const tps::real& x2, const tps::real& p);

	tps::real x(tps::real t) const override;
	tps::real y(tps::real t) const override;
	tps::real dx(tps::real t) const override;
	tps::real dy(tps::real t) const override;
  tps::real d2x(tps::real t) const override;
  tps::real d2y(tps::real t) const override;

	tps::real length() const override;

	ProtoPtr<Curve> clone() const override;

private:
	tps::real x1;
	tps::real x2;
	tps::real p;
	tps::real lengthInt(tps::real x) const;    //Int(sqrt(1+x^2)) which is used for parabola length calculation
};

}




#endif /* CURVE_H_ */

