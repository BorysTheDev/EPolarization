#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_
#include "matrix.h"
#include "helper.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "discretize_curve.h"
#include "types.h"
#include <atomic>

class Discretization {
	typedef IncidentFieldPackage IncidentFields;
    typedef std::vector<DiscretizeCurve::Ptr> CurvesList;

public:
	Discretization(const CurvesList& sCurves, const IncidentFields& fields);

	MatrixPtr<types::complex> createMatrix(int threads = 4);
    std::vector<types::complex> createArray();

private:
	size_t size = 0;


	const IncidentFields& fields;
	const CurvesList& curves;

	//waveNumber
	const types::real wN;
	// contour < border
	std::vector<int> borders;
	//left border of contour
	int leftBorderOf(int c) {return c == 0 ? 0 : borders[c - 1] ;}
	void fillMatrixBlock(Matrix<types::complex>&, size_t c1, size_t c2, int);

	//Index taskIndex;
};

#endif /* DISCRETIZATION_H_ */
