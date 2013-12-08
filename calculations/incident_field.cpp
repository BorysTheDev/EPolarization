#include "incident_field.h"
tps::complex EPolarizationField::operator()(tps::real x1, tps::real x2)const {
	tps::real expArg = (x1 * cos(this->alpha_) + x2 * sin(this->alpha_))
			* this->waveNumber_;
	return exp(tps::complex(0, -expArg));
}
