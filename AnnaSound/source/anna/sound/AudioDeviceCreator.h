#ifndef AUDIODEVICECREATOR_H
#define AUDIODEVICECREATOR_H

#include "AudioDevice.h"
#include <map>

namespace anna {
namespace sound {

class AudioDeviceCreator {
public:
	inline virtual ~AudioDeviceCreator(void);
	virtual AudioDevice* createAudioDevice(
		std::map<AudioDevice::ATTRIBUTE, int> context_attributes =
		std::map<AudioDevice::ATTRIBUTE, int>())
		throw(exceptions::CreationException) = 0;
};

AudioDeviceCreator::~AudioDeviceCreator() {}

}
}
#endif
