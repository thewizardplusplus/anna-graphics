#include "AnimateTrack.h"
#include <algorithm>

using namespace thewizardplusplus::anna::graphics;

size_t AnimateTrack::getNumberOfKeys(void) const {
	return keys.size();
}

AnimateKey AnimateTrack::getKey(size_t number) const {
	if (number < keys.size()) {
		return keys[number];
	} else {
		return AnimateKey();
	}
}

void AnimateTrack::addKey(const AnimateKey& key) {
	keys.push_back(key);
}

void AnimateTrack::removeKey(const AnimateKey& key) {
	AnimateKeyVector::iterator index = std::find(keys.begin(), keys.end(), key);
	if (index != keys.end()) {
		keys.erase(index);
	}
}

size_t AnimateTrack::getNumberOfFrames(void) const {
	size_t number_of_frames = 0;
	AnimateKeyVector::const_iterator i = keys.begin();
	for (; i != keys.end(); ++i) {
		size_t frame = (*i).frame;
		if (frame > number_of_frames) {
			number_of_frames = frame;
		}
	}

	return number_of_frames;
}
