#ifndef FOGPARAMETERS_H
#define FOGPARAMETERS_H

#include "FogType.h"
#include "Vector3D.h"

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

	FogParameters(void);
	FogParameters(const maths::Vector3D<float>& color, float density, float
		start_depth, float end_depth, FogType::Types type = FogType::LINEAR);
};

}
}
}
#endif
