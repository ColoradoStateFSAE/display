#include "convert.h"

namespace convert {
	double k_to_f(double value) {
		return (9.0 / 5) * (value - 273.15) + 32;
	}

	double kpa_to_psi(double value) {
		return value / 6.895;
	}
}
