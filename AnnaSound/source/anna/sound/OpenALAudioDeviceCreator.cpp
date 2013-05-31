#include "OpenALAudioDeviceCreator.h"
#include "../utils/allocation.h"
#include "OpenALAudioDevice.h"

using namespace anna::sound;

AudioDevice* OpenALAudioDeviceCreator::createAudioDevice(
	std::map<AudioDevice::ATTRIBUTE, int> context_attributes)
	throw(exceptions::CreationException)
{
	AudioDevice* audio_device = NULL;
	ALLOCATION(OpenALAudioDevice, audio_device, context_attributes);
	return audio_device;
}
