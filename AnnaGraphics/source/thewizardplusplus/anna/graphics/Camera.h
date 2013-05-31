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

	CameraType::Types      type;
	float                  near_plane;
	float                  far_plane;
	maths::Vector3D<float> position;
	maths::Vector3D<float> rotation;

	explicit Camera(CameraType::Types type = CameraType::PERSPECTIVE,
		float near_plane = 0.1f, float far_plane = 100.0f, const maths::
		Vector3D<float>& position = maths::Vector3D<float>(), const maths::
		Vector3D<float>& rotation = maths::Vector3D<float>());
};

}
}
}
#endif
