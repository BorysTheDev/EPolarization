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
#include <array>
#include <atomic>
/*
struct SubIndex
{
  int m,n,s;
};

class Index
{
public:
  Index(std::array<int, 2> borders, int start): i(start), borders(borders) {}
  inline SubIndex getNext();
private:
  std::atomic_int i;
  std::array<int, 2> borders;
};

SubIndex Index::getNext()
{
  int k = i++;
  int s2 = k / borders[1];
  return {s2 / borders[0], s2 % borders[0], k % borders[1]};
}*/

class Discretization {
	typedef IncidentFieldPackage IncidentFields;
	typedef Box<DiscretizeCurve> CurvesList;

public:
	Discretization(const CurvesList& sCurves, const IncidentFields& fields);

	MatrixPtr<types::complex> createMatrix(int threads = 4);
	ArrayPtr<types::complex> createArray();

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
