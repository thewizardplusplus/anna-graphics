#include "Camera.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

const float Camera::FOV = 45.0f;

Camera::Camera(CameraType::Types type, float near_plane, float far_plane, const
	Vector3D<float>& position, const Vector3D<float>& rotation)
:
	type(type),
	near_plane(near_plane),
	far_plane(far_plane),
	position(position),
	rotation(rotation)
{}

CameraType::Types Camera::getType(void) const {
	return type;
}

void Camera::setType(CameraType::Types type) {
	this->type = type;
}

float Camera::getNearPlane(void) const {
	return near_plane;
}

void Camera::setNearPlane(float near_plane) {
	this->near_plane = near_plane;
}

float Camera::getFarPlane(void) const {
	return far_plane;
}

void Camera::setFarPlane(float far_plane) {
	this->far_plane = far_plane;
}

Vector3D<float> Camera::getPosition(void) const {
	return position;
}

void Camera::setPosition(const Vector3D<float>& position) {
	this->position = position;
}

void Camera::setPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}

Vector3D<float> Camera::getRotation(void) const {
	return rotation;
}

void Camera::setRotation(const Vector3D<float>& rotation) {
	this->rotation = rotation;
}

void Camera::setRotation(float x, float y, float z) {
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}
