#include "Maths.h"
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <ctime>

using namespace thewizardplusplus::anna::maths;

const float Maths::PI = 3.14159f;

bool Maths::initialize_prmg = false;

bool Maths::isEqual(float x, float y, int bits_not_compare) {
	return std::abs(x - y) <= (1 << bits_not_compare) * FLT_EPSILON *
		std::max(std::abs(x), std::abs(y));
}

bool Maths::isEqual(double x, double y, int bits_not_compare) {
	return std::abs(x - y) <= (1 << bits_not_compare) * DBL_EPSILON *
		std::max(std::abs(x), std::abs(y));
}

bool Maths::isEqual(long double x, long double y, int bits_not_compare) {
	return std::abs(x - y) <= (1 << bits_not_compare) * LDBL_EPSILON *
		std::max(std::abs(x), std::abs(y));
}

bool Maths::isNull(float x, int bits_not_compare) {
	return std::abs(x) <= (1 << bits_not_compare) * FLT_EPSILON * std::abs(x);
}

bool Maths::isNull(double x, int bits_not_compare) {
	return std::abs(x) <= (1 << bits_not_compare) * DBL_EPSILON * std::abs(x);
}

bool Maths::isNull(long double x, int bits_not_compare) {
	return std::abs(x) <= (1 << bits_not_compare) * LDBL_EPSILON * std::abs(x);
}

float Maths::toDegrees(float angle) {
	return 180.0f * angle / PI;
}

float Maths::toRadians(float angle) {
	return PI * angle / 180.0f;
}

float Maths::clamp(float number, float limit1, float limit2) {
	float minimal_value = std::min(limit1, limit2);
	float maximal_value = std::max(limit1, limit2);

	if (number < minimal_value) {
		number = minimal_value;
	} else if (number > maximal_value) {
		number = maximal_value;
	}

	return number;
}

float Maths::interpolate(float x1, float x2, float shift) {
	return x1 + clamp(shift) * (x2 - x1);
}

float Maths::randomNumber(float limit1, float limit2) {
	if (!initialize_prmg) {
		std::srand(std::time(NULL));
		initialize_prmg = true;
	}

	float minimal_value = std::min(limit1, limit2);
	float maximal_value = std::max(limit1, limit2);

	return static_cast<float>(std::rand()) / RAND_MAX *
		(maximal_value - minimal_value) + minimal_value;
}
