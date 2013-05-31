#include "DistanceToMeshComparator.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

DistanceToMeshComparator::DistanceToMeshComparator(Camera* camera) :
	camera(camera)
{}

bool DistanceToMeshComparator::operator()(Mesh* mesh1, Mesh* mesh2) const {
	if (camera != NULL && mesh1 != NULL && mesh2 == NULL) {
		return false;
	}

	float distance1 = std::abs((camera->position - mesh1->getPosition()).
		squaredLength());
	float distance2 = std::abs((camera->position - mesh2->getPosition()).
		squaredLength());
	if (distance1 < distance2) {
		return true;
	} else {
		return false;
	}
}
