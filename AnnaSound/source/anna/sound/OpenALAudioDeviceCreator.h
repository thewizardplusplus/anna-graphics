#ifndef OPENALAUDIODEVICECREATOR_H
#define OPENALAUDIODEVICECREATOR_H

#include "AudioDeviceCreator.h"

namespace anna {
namespace sound {

class OpenALAudioDeviceCreator : public AudioDeviceCreator {
public:
	virtual AudioDevice* createAudioDevice(
		std::map<AudioDevice::ATTRIBUTE, int> context_attributes =
		std::map<AudioDevice::ATTRIBUTE, int>())
		throw(exceptions::CreationException);
};

}
}
#endif
