#include "helper.h"
#include "math/simple_math.h"

using namespace mth;

double ch1Nodes(const int n, const int i) {
	return cos((2.0 * i + 1.0) * M_PI / (2.0 * n));
}

namespace epol {

types::complex lim(types::RPoint d, types::real k) {
	return -types::complex(0, 2 / M_PI)
			* (log(k * sqrt(sqr(d.x) + sqr(d.y)) / 2) - M_PI / types::complex(0, 2) + gamma);
}

types::real Ln(const types::real& t0, const types::real& t_, const int n) {
	double sum = 0;
	for (int p = 1; p < n; p++) {
		sum += ch1(p, t_) * ch1(p, t0) / p;
	}
	return -(log(2) + 2 * sum);
}
}
