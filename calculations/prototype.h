/*
 * prototype.h
 *
 *  Created on: 30.05.2013
 *      Author: equal
 */

#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_

template <class T>
class Prototype{
public:
	virtual T* clone() const = 0;
	virtual ~Prototype(){}
};



#endif /* PROTOTYPE_H_ */
