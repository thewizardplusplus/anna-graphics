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
