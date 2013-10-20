#ifndef FOGPARAMETERS_H
#define FOGPARAMETERS_H

#include "FogType.h"
#include "../maths/Vector3D.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class FogParameters {
public:
	FogType::Types         type;
	maths::Vector3D<float> color;
	float                  density;
	float                  start_depth;
	float                  end_depth;

	FogParameters(const maths::Vector3D<float>& color = maths::Vector3D<float>(
		0.5f, 0.5f, 0.5f), float density = 1.0f, float start_depth = 0.1f, float
		end_depth = 5000.0f, FogType::Types type = FogType::LINEAR);
};

}
}
}
#endif
