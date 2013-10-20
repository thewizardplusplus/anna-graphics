#include "FogParameters.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

FogParameters::FogParameters(const Vector3D<float>& color, float density, float
	start_depth, float end_depth, FogType::Types type)
:
	type(type),
	color(color),
	density(density),
	start_depth(start_depth),
	end_depth(end_depth)
{}
