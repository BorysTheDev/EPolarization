#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_
#include "array.h"
#include "matrix.h"
#include "helper.h"
#include "incident_field.h"
#include "incident_field_package.h"
#include "discretize_curve.h"
#include "box.h"
#include "types.h"

class Discretization {
	typedef IncidentFieldPackage IncidentFieldsList;
	typedef Box<DiscretizeCurve> CurvesList;

public:
	Discretization(const CurvesList& sCurves, const IncidentFieldsList& fields);

	MatrixPtr<types::complex> createMatrix();
	ArrayPtr<types::complex> createArray();

private:
	size_t size;
	types::real waveNumber;

	const IncidentFieldsList& fields;
	const CurvesList& curves;

	static void fillMatrixBlock(Matrix<types::complex>& matr, size_t startI, size_t startJ,
			const DiscretizeCurve& c1, const DiscretizeCurve& c2,types::real);

};

#endif /* DISCRETIZATION_H_ */
