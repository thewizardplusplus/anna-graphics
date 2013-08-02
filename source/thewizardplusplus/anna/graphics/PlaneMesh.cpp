#include "PlaneMesh.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

PlaneMesh::PlaneMesh(Object* object) :
	Mesh(object)
{
	addVertex(new Vertex(Vector3D<float>(-1.0f, -1.0f, 0.0f), Vector2D<float>(
		0.0f, 0.0f)));
	addVertex(new Vertex(Vector3D<float>(1.0f, -1.0f, 0.0f), Vector2D<float>(
		1.0f, 0.0f)));
	addVertex(new Vertex(Vector3D<float>(1.0f, 1.0f, 0.0f), Vector2D<float>(
		1.0f, 1.0f)));
	addVertex(new Vertex(Vector3D<float>(-1.0f, -1.0f, 0.0f), Vector2D<float>(
		0.0f, 0.0f)));
	addVertex(new Vertex(Vector3D<float>(1.0f, 1.0f, 0.0f), Vector2D<float>(
		1.0f, 1.0f)));
	addVertex(new Vertex(Vector3D<float>(-1.0f, 1.0f, 0.0f), Vector2D<float>(
		0.0f, 1.0f)));
}
