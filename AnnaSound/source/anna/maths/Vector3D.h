#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>
#include <string>
#include <sstream>

namespace anna {
namespace maths {

template<typename Type>
class Vector3D {
public:
	Type x;
	Type y;
	Type z;

	inline Vector3D(void);
	inline Vector3D(Type x, Type y, Type z);
	inline bool operator==(const Vector3D<Type>& vector) const;
	inline bool operator!=(const Vector3D<Type>& vector) const;
	inline Vector3D<Type> operator-(void) const;
	inline Vector3D<Type> operator+(const Vector3D<Type>& vector) const;
	inline Vector3D<Type> operator+=(const Vector3D<Type>& vector);
	inline Vector3D<Type> operator-(const Vector3D<Type>& vector) const;
	inline Vector3D<Type> operator-=(const Vector3D<Type>& vector);
	inline Vector3D<Type> operator*(const Vector3D<Type>& vector) const;
	inline Vector3D<Type> operator*=(const Vector3D<Type>& vector);
	inline Vector3D<Type> operator*(Type number) const;
	inline Vector3D<Type> operator*=(Type number);
	inline Vector3D<Type> operator/(Type number) const;
	inline Vector3D<Type> operator/=(Type number);
	inline Type dot(const Vector3D<Type>& vector) const;
	inline Vector3D<Type> cross(const Vector3D<Type>& vector) const;
	inline Type squaredLength(void) const;
	inline Type length(void) const;
	inline Vector3D<Type> normalized(void) const;
	inline void normalize(void);
	inline std::string toString(void) const;
};

template<typename Type>
Vector3D<Type>::Vector3D(void) :
	x(0),
	y(0),
	z(0)
{}

template<typename Type>
Vector3D<Type>::Vector3D(Type x, Type y, Type z) :
	x(x),
	y(y),
	z(z)
{}

template<typename Type>
bool Vector3D<Type>::operator==(const Vector3D<Type>& vector) const {
	return x == vector.x && y == vector.y && z == vector.z;
}

template<typename Type>
bool Vector3D<Type>::operator!=(const Vector3D<Type>& vector) const {
	return x != vector.x || y != vector.y || z != vector.z;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::operator-(void) const {
	Vector3D<Type> result;
	result.x = -x;
	result.y = -y;
	result.z = -z;
	return result;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::operator+(const Vector3D<Type>& vector) const {
	Vector3D<Type> result;
	result.x = x + vector.x;
	result.y = y + vector.y;
	result.z = z + vector.z;
	return result;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::operator+=(const Vector3D<Type>& vector) {
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::operator-(const Vector3D<Type>& vector) const {
	Vector3D<Type> result;
	result.x = x - vector.x;
	result.y = y - vector.y;
	result.z = z - vector.z;
	return result;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::operator-=(const Vector3D<Type>& vector) {
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::operator*(const Vector3D<Type>& vector) const {
	Vector3D<Type> result;
	result.x = x * vector.x;
	result.y = y * vector.y;
	result.z = z * vector.z;
	return result;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::operator*=(const Vector3D<Type>& vector) {
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	return *this;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::operator*(Type number) const {
	Vector3D<Type> result;
	result.x = x * number;
	result.y = y * number;
	result.z = z * number;
	return result;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::operator*=(Type number) {
	x *= number;
	y *= number;
	z *= number;
	return *this;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::operator/(Type number) const {
	Vector3D<Type> result;
	if (number != 0) {
		result.x = x / number;
		result.y = y / number;
		result.z = z / number;
	}
	return result;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::operator/=(Type number) {
	if (number != 0) {
		x /= number;
		y /= number;
		z /= number;
	}
	return *this;
}

template<typename Type>
Type Vector3D<Type>::dot(const Vector3D<Type>& vector) const {
	return x * vector.x + y * vector.y + z * vector.z;
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::cross(const Vector3D<Type>& vector) const {
	Vector3D<Type> result;
	result.x = y * vector.z - z * vector.y;
	result.y = z * vector.x - x * vector.z;
	result.z = x * vector.y - y * vector.x;
	return result;
}

template<typename Type>
Type Vector3D<Type>::squaredLength(void) const {
	return x * x + y * y + z * z;
}

template<typename Type>
Type Vector3D<Type>::length(void) const {
	return std::sqrt(x * x + y * y + z * z);
}

template<typename Type>
Vector3D<Type> Vector3D<Type>::normalized(void) const {
	Vector3D<Type> result;
	Type length = this->length();
	if (length != 0) {
			result.x = x / length;
			result.y = y / length;
			result.z = z / length;
	}
	return result;
}

template<typename Type>
void Vector3D<Type>::normalize(void) {
	Type length = this->length();
	if (length != 0) {
			x /= length;
			y /= length;
			z /= length;
	}
}

template<typename Type>
std::string Vector3D<Type>::toString(void) const {
	std::ostringstream stream;
	stream << "Vector3D(" << x << "; " << y << "; " << z << ")";
	return stream.str();
}

}
}
#endif
