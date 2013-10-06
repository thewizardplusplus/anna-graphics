#ifndef MATHS_H
#define MATHS_H

namespace thewizardplusplus {
namespace anna {
namespace maths {

class Maths {
public:
	static const float PI;
	static const int   DEFAULT_BITS_NOT_COMPARE = 4;

	static bool isEqual(float x, float y, int bits_not_compare =
		DEFAULT_BITS_NOT_COMPARE);
	static bool isEqual(double x, double y, int bits_not_compare =
		DEFAULT_BITS_NOT_COMPARE);
	static bool isEqual(long double x, long double y, int bits_not_compare =
		DEFAULT_BITS_NOT_COMPARE);
	static bool isNull(float x, int bits_not_compare =
		DEFAULT_BITS_NOT_COMPARE);
	static bool isNull(double x, int bits_not_compare =
		DEFAULT_BITS_NOT_COMPARE);
	static bool isNull(long double x, int bits_not_compare =
		DEFAULT_BITS_NOT_COMPARE);
	static float toDegrees(float angle);
	static float toRadians(float angle);
	static float clamp(float number, float limit1 = 1.0f, float limit2 = 0.0f);
	static float interpolate(float x1, float x2, float shift);
	static float randomNumber(float limit1 = 1.0f, float limit2 = 0.0f);

private:
	static bool initialize_prmg;
};

}
}
}
#endif
