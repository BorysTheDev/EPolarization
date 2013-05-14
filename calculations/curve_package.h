#ifndef CURVE_PACKAGE_H_
#define CURVE_PACKAGE_H_
#include "curve.h"
#include <stdexcept>

template<class T>
class CurvePackage {
public:
	typedef Array<const Curve<T>*> Curves;

	//constructors
	explicit CurvePackage(size_t size = 1) : curves(size), filled(0) {}

	//functions
	size_t size() {return curves.size();}

	void addCurve(const Curve<T>& curve) {curves[filled++] = curve.clone();}

	const Curve<T>& operator[](const size_t n)const {return *curves[n];}

	//destructor
	~CurvePackage();

private:
	Curves curves;
	size_t filled;
	//this function have not to be used
	typedef CurvePackage<T> cPack;
	CurvePackage(const cPack&) = delete;
	const cPack& operator= (const cPack& f) = delete;
};

template<class T>
CurvePackage<T>::~CurvePackage(){
	for (size_t i = 0; i < curves.size(); i++){
		if (curves[i]) delete curves[i];
	}
}

#endif /* CURVE_PACKAGE_H_ */
