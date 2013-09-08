#include "incident_field.h"
types::complex EPolarizationField::operator()(types::real x1, types::real x2)const {
	types::real expArg = (x1 * cos(this->alpha_) + x2 * sin(this->alpha_))
			* this->waveNumber_;
	return exp(types::complex(0, -expArg));
}
