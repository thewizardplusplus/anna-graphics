#ifndef ANIMATETRACK_H
#define ANIMATETRACK_H

#include "AnimateKey.h"
#include <vector>
#include <cstdlib>

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class AnimateTrack {
public:
	size_t getNumberOfKeys(void) const;
	AnimateKey getKey(size_t number) const;
	void addKey(const AnimateKey& key);
	void removeKey(const AnimateKey& key);
	size_t getNumberOfFrames(void) const;

private:
	typedef std::vector<AnimateKey> AnimateKeyVector;

	AnimateKeyVector keys;
};

}
}
}
#endif
