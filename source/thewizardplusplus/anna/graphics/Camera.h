#ifndef CAMERA_H
#define CAMERA_H

#include "CameraType.h"
#include "../maths/Vector3D.h"
#include "../maths/Vector4D.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class Camera {
public:
	static const float FOV;

	explicit Camera(CameraType::Types type = CameraType::PERSPECTIVE,
		float near_plane = 0.1f, float far_plane = 100.0f, const maths::
		Vector3D<float>& position = maths::Vector3D<float>(), const maths::
		Vector3D<float>& rotation = maths::Vector3D<float>());
	CameraType::Types getType(void) const;
	void setType(CameraType::Types type);
	float getNearPlane(void) const;
	void setNearPlane(float near_plane);
	float getFarPlane(void) const;
	void setFarPlane(float far_plane);
	maths::Vector3D<float> getPosition(void) const;
	void setPosition(const maths::Vector3D<float>& position);
	void setPosition(float x, float y, float z);
	maths::Vector3D<float> getRotation(void) const;
	void setRotation(const maths::Vector3D<float>& rotation);
	void setRotation(float x, float y, float z);

private:
	CameraType::Types      type;
	float                  near_plane;
	float                  far_plane;
	maths::Vector3D<float> position;
	maths::Vector3D<float> rotation;
};

}
}
}
#endif
