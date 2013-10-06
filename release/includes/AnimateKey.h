#ifndef ANIMATEKEY_H
#define ANIMATEKEY_H

#include "AnimateKeyType.h"
#include "Vector3D.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class AnimateKey {
public:
	bool                   valid;
	size_t                 index_of_mesh;
	size_t                 frame;
	AnimateKeyType::Types  type;
	maths::Vector3D<float> transformation;

	AnimateKey(void);
	AnimateKey(size_t index_of_mesh, size_t frame, AnimateKeyType::Types type,
		maths::Vector3D<float> transformation);
	bool operator==(const AnimateKey& animate_key);
};

}
}
}
#endif
