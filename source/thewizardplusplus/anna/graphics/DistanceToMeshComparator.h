#ifndef DISTANCETOMESHCOMPARATOR_H
#define DISTANCETOMESHCOMPARATOR_H

#include "Camera.h"
#include "Mesh.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class DistanceToMeshComparator {
public:
	explicit DistanceToMeshComparator(Camera* camera);
	bool operator()(Mesh* mesh1, Mesh* mesh2) const;

private:
	Camera* camera;
};

}
}
}
#endif
