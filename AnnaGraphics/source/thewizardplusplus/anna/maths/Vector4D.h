#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "Maths.h"
#include <string>
#include <cmath>
#include <sstream>

namespace thewizardplusplus {
namespace anna {
namespace maths {

template<typename Type>
class Vector4D {
public:
	Type x;
	Type y;
	Type z;
	Type w;

	inline Vector4D(void);
	inline Vector4D(Type x, Type y, Type z, Type w);
	inline bool operator==(const Vector4D<Type>& vector) const;
	inline bool operator!=(const Vector4D<Type>& vector) const;
	inline Vector4D<Type> operator-(void) const;
	inline Vector4D<Type> operator+(const Vector4D<Type>& vector) const;
	inline Vector4D<Type> operator+=(const Vector4D<Type>& vector);
	inline Vector4D<Type> operator-(const Vector4D<Type>& vector) const;
	inline Vector4D<Type> operator-=(const Vector4D<Type>& vector);
	inline Vector4D<Type> operator*(const Vector4D<Type>& vector) const;
	inline Vector4D<Type> operator*=(const Vector4D<Type>& vector);
	inline Vector4D<Type> operator*(Type number) const;
	inline Vector4D<Type> operator*=(Type number);
	inline Vector4D<Type> operator/(Type number) const;
	inline Vector4D<Type> operator/=(Type number);
	inline bool isApproximatelyEqualTo(const Vector4D<Type>& vector) const;
	inline Type dot(const Vector4D<Type>& vector) const;
	inline Type squaredLength(void) const;
	inline Type length(void) const;
	inline Vector4D<Type> normalized(void) const;
	inline void normalize(void);
	inline Vector4D interpolatedTo(const Vector4D& target, float shift) const;
	inline Vector4D interpolateTo(const Vector4D& target, float shift);
	inline std::string toString(void) const;
};

template<typename Type>
Vector4D<Type>::Vector4D(void) :
	x(0),
	y(0),
	z(0),
	w(0)
{}

template<typename Type>
Vector4D<Type>::Vector4D(Type x, Type y, Type z, Type w) :
	x(x),
	y(y),
	z(z),
	w(w)
{}

template<typename Type>
bool Vector4D<Type>::operator==(const Vector4D<Type>& vector) const {
	return x == vector.x && y == vector.y && z == vector.z && w == vector.w;
}

template<typename Type>
bool Vector4D<Type>::operator!=(const Vector4D<Type>& vector) const {
	return x != vector.x || y != vector.y || z != vector.z || w != vector.w;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::operator-(void) const {
	Vector4D<Type> result;
	result.x = -x;
	result.y = -y;
	result.z = -z;
	result.w = -w;

	return result;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::operator+(const Vector4D<Type>& vector) const {
	Vector4D<Type> result;
	result.x = x + vector.x;
	result.y = y + vector.y;
	result.z = z + vector.z;
	result.w = w + vector.w;

	return result;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::operator+=(const Vector4D<Type>& vector) {
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;

	return *this;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::operator-(const Vector4D<Type>& vector) const {
	Vector4D<Type> result;
	result.x = x - vector.x;
	result.y = y - vector.y;
	result.z = z - vector.z;
	result.w = w - vector.w;

	return result;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::operator-=(const Vector4D<Type>& vector) {
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;

	return *this;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::operator*(const Vector4D<Type>& vector) const {
	Vector4D<Type> result;
	result.x = x * vector.x;
	result.y = y * vector.y;
	result.z = z * vector.z;
	result.w = w * vector.w;

	return result;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::operator*=(const Vector4D<Type>& vector) {
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	w *= vector.w;

	return *this;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::operator*(Type number) const {
	Vector4D<Type> result;
	result.x = x * number;
	result.y = y * number;
	result.z = z * number;
	result.w = w * number;

	return result;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::operator*=(Type number) {
	x *= number;
	y *= number;
	z *= number;
	w *= number;

	return *this;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::operator/(Type number) const {
	Vector4D<Type> result;
	result.x = x / number;
	result.y = y / number;
	result.z = z / number;
	result.w = w / number;

	return result;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::operator/=(Type number) {
	x /= number;
	y /= number;
	z /= number;
	w /= number;

	return *this;
}

template<typename Type>
bool Vector4D<Type>::isApproximatelyEqualTo(const Vector4D<Type>& vector) const
{
	return Maths::isEqual(x, vector.x) && Maths::isEqual(y, vector.y) &&
		Maths::isEqual(z, vector.z) && Maths::isEqual(w, vector.w);
}

template<typename Type>
Type Vector4D<Type>::dot(const Vector4D<Type>& vector) const {
	return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
}

template<typename Type>
Type Vector4D<Type>::squaredLength(void) const {
	return x * x + y * y + z * z + w * w;
}

template<typename Type>
Type Vector4D<Type>::length(void) const {
	return std::sqrt(x * x + y * y + z * z + w * w);
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::normalized(void) const {
	Vector4D<Type> result;
	Type length = this->length();
	if (length != 0) {
		result.x = x / length;
		result.y = y / length;
		result.z = z / length;
		result.w = w / length;
	}

	return result;
}

template<typename Type>
void Vector4D<Type>::normalize(void) {
	Type length = this->length();
	if (length != 0) {
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::interpolatedTo(const Vector4D<Type>& target,
	float shift) const
{
	Vector4D<Type> result;
	result.x = Maths::interpolate(x, target.x, shift);
	result.y = Maths::interpolate(y, target.y, shift);
	result.z = Maths::interpolate(z, target.z, shift);
	result.w = Maths::interpolate(w, target.w, shift);

	return result;
}

template<typename Type>
Vector4D<Type> Vector4D<Type>::interpolateTo(const Vector4D<Type>& target,
	float shift)
{
	x = Maths::interpolate(x, target.x, shift);
	y = Maths::interpolate(y, target.y, shift);
	z = Maths::interpolate(z, target.z, shift);
	w = Maths::interpolate(w, target.w, shift);

	return *this;
}

template<typename Type>
std::string Vector4D<Type>::toString(void) const {
	std::ostringstream out;
	out << "Vector4D(" << x << ", " << y << ", " << z << ", " << w << ")";

	std::string result = out.str();
	return result;
}

}
}
}
#endif
