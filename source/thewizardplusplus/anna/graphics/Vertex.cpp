#include "Vertex.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

Vertex::Vertex(const Vector3D<float>& position, const Vector2D<float>& uv) :
	position(position),
	uv(uv)
{}
