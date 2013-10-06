#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3D.h"
#include "Vector2D.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class Vertex {
public:
	maths::Vector3D<float> position;
	maths::Vector2D<float> uv;

	Vertex(const maths::Vector3D<float>& position = maths::Vector3D<float>(),
		const maths::Vector2D<float>& uv = maths::Vector2D<float>());
};

}
}
}
#endif
