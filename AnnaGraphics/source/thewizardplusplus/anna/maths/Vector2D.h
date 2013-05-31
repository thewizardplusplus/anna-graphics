#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "Maths.h"
#include <string>
#include <cmath>
#include <sstream>

namespace thewizardplusplus {
namespace anna {
namespace maths {

template<typename Type>
class Vector2D {
public:
	Type x;
	Type y;

	inline Vector2D(void);
	inline Vector2D(Type x, Type y);
	inline bool operator==(const Vector2D<Type>& vector) const;
	inline bool operator!=(const Vector2D<Type>& vector) const;
	inline Vector2D<Type> operator-(void) const;
	inline Vector2D<Type> operator+(const Vector2D<Type>& vector) const;
	inline Vector2D<Type> operator+=(const Vector2D<Type>& vector);
	inline Vector2D<Type> operator-(const Vector2D<Type>& vector) const;
	inline Vector2D<Type> operator-=(const Vector2D<Type>& vector);
	inline Vector2D<Type> operator*(const Vector2D<Type>& vector) const;
	inline Vector2D<Type> operator*=(const Vector2D<Type>& vector);
	inline Vector2D<Type> operator*(Type number) const;
	inline Vector2D<Type> operator*=(Type number);
	inline Vector2D<Type> operator/(Type number) const;
	inline Vector2D<Type> operator/=(Type number);
	inline bool isApproximatelyEqualTo(const Vector2D<Type>& vector) const;
	inline Type dot(const Vector2D<Type>& vector) const;
	inline Type squaredLength(void) const;
	inline Type length(void) const;
	inline Vector2D<Type> normalized(void) const;
	inline void normalize(void);
	inline Vector2D interpolatedTo(const Vector2D& target, float shift) const;
	inline Vector2D interpolateTo(const Vector2D& target, float shift);
	inline std::string toString(void) const;
};

template<typename Type>
Vector2D<Type>::Vector2D(void) :
	x(0),
	y(0)
{}

template<typename Type>
Vector2D<Type>::Vector2D(Type x, Type y) :
	x(x),
	y(y)
{}

template<typename Type>
bool Vector2D<Type>::operator==(const Vector2D<Type>& vector) const {
	return x == vector.x && y == vector.y;
}

template<typename Type>
bool Vector2D<Type>::operator!=(const Vector2D<Type>& vector) const {
	return x != vector.x || y != vector.y;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::operator-(void) const {
	Vector2D<Type> result;
	result.x = -x;
	result.y = -y;

	return result;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::operator+(const Vector2D<Type>& vector) const {
	Vector2D<Type> result;
	result.x = x + vector.x;
	result.y = y + vector.y;

	return result;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::operator+=(const Vector2D<Type>& vector) {
	x += vector.x;
	y += vector.y;

	return *this;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::operator-(const Vector2D<Type>& vector) const {
	Vector2D<Type> result;
	result.x = x - vector.x;
	result.y = y - vector.y;

	return result;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::operator-=(const Vector2D<Type>& vector) {
	x -= vector.x;
	y -= vector.y;

	return *this;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::operator*(const Vector2D<Type>& vector) const {
	Vector2D<Type> result;
	result.x = x * vector.x;
	result.y = y * vector.y;

	return result;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::operator*=(const Vector2D<Type>& vector) {
	x *= vector.x;
	y *= vector.y;

	return *this;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::operator*(Type number) const {
	Vector2D<Type> result;
	result.x = x * number;
	result.y = y * number;

	return result;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::operator*=(Type number) {
	x *= number;
	y *= number;

	return *this;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::operator/(Type number) const {
	Vector2D<Type> result;
	result.x = x / number;
	result.y = y / number;

	return result;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::operator/=(Type number) {
	x /= number;
	y /= number;

	return *this;
}

template<typename Type>
bool Vector2D<Type>::isApproximatelyEqualTo(const Vector2D<Type>& vector) const
{
	return Maths::isEqual(x, vector.x) && Maths::isEqual(y, vector.y);
}

template<typename Type>
Type Vector2D<Type>::dot(const Vector2D<Type>& vector) const {
	return x * vector.x + y * vector.y;
}

template<typename Type>
Type Vector2D<Type>::squaredLength(void) const {
	return x * x + y * y;
}

template<typename Type>
Type Vector2D<Type>::length(void) const {
	return std::sqrt(x * x + y * y);
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::normalized(void) const {
	Vector2D<Type> result;
	Type length = this->length();
	if (length != 0) {
		result.x = x / length;
		result.y = y / length;
	}

	return result;
}

template<typename Type>
void Vector2D<Type>::normalize(void) {
	Type length = this->length();
	if (length != 0) {
		x /= length;
		y /= length;
	}
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::interpolatedTo(const Vector2D<Type>& target,
	float shift) const
{
	Vector2D<Type> result;
	result.x = Maths::interpolate(x, target.x, shift);
	result.y = Maths::interpolate(y, target.y, shift);

	return result;
}

template<typename Type>
Vector2D<Type> Vector2D<Type>::interpolateTo(const Vector2D<Type>& target,
	float shift)
{
	x = Maths::interpolate(x, target.x, shift);
	y = Maths::interpolate(y, target.y, shift);

	return *this;
}

template<typename Type>
std::string Vector2D<Type>::toString(void) const {
	std::ostringstream out;
	out << "Vector2D(" << x << ", " << y << ")";

	std::string result = out.str();
	return result;
}

}
}
}
#endif
