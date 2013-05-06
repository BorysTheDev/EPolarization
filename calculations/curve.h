#ifndef CURVE_H_
#define CURVE_H_

//TODO it's must be spline or general function
template<class T>
class Curve{
public:
	virtual T x1(T t) const = 0;
	virtual T x2(T t) const = 0;
	//pattern prototype
	virtual Curve* clone() const = 0;

	virtual ~Curve(){}
};

//TODO need to add parameters and constructor and redefinition method clone
template<class T>
class Parabola: public Curve<T>{
public:
	T x1(T t) const override {return t;}
	T x2(T t) const override {return t * t / 2;}

	Parabola* clone() const override {return new Parabola();}

	~Parabola(){Curve<T>::~Curve();}
};

#endif /* CURVE_H_ */
