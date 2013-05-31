#include "AnimateKey.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

AnimateKey::AnimateKey(void) :
	valid(false),
	index_of_mesh(0),
	frame(0),
	type(AnimateKeyType::POSITION)
{}

AnimateKey::AnimateKey(size_t index_of_mesh, size_t frame, AnimateKeyType::Types
	type, Vector3D<float> transformation)
:
	valid(true),
	index_of_mesh(index_of_mesh),
	frame(frame),
	type(type),
	transformation(transformation)
{}

bool AnimateKey::operator==(const AnimateKey& animate_key) {
	return animate_key.valid == animate_key.valid && animate_key.index_of_mesh
		== animate_key.index_of_mesh && animate_key.frame == animate_key.frame
		&& animate_key.type == animate_key.type && animate_key.transformation ==
		animate_key.transformation;
}
