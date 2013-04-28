/*
 * curve.h
 *
 *  Created on: 28.04.2013
 *      Author: equal
 */

#ifndef CURVE_H_
#define CURVE_H_

//TODO you must make it how incident field class
template<class T>
class Curve{
public:
	T x1(T t) {return t;}
	T x2(T t) {return t * t / 2;}
};



#endif /* CURVE_H_ */
