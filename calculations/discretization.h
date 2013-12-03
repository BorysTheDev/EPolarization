#ifndef DISCRETIZATION_H_
#define DISCRETIZATION_H_
#include "array.h"
#include "matrix.h"
#include "helper.h"
#include "incident_field.h"
#include "discretize_curve.h"
#include "box.h"
#include "types.h"

class Discretization {
	typedef std::vector<ProtoPtr<IncidentField> > IncidentFieldsList;
	typedef Box<crv::DiscretizeCurve> CurvesList;

public:
	Discretization(const CurvesList& sCurves, const IncidentFieldsList& fields);

	MatrixPtr<tps::complex> createMatrix();
	ArrayPtr<tps::complex> createArray();

private:
	size_t size;
	tps::real waveNumber;

	const IncidentFieldsList& fields;
	const CurvesList& curves;

	static void fillMatrixBlock(Matrix<tps::complex>& matr, size_t startI, size_t startJ,
			const crv::DiscretizeCurve& c1, const crv::DiscretizeCurve& c2,tps::real);

};

#endif /* DISCRETIZATION_H_ */
