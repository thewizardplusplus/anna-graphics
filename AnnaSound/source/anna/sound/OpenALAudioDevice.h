#ifndef OPENALAUDIODEVICE_H
#define OPENALAUDIODEVICE_H

#include "AudioDevice.h"
#include <AL/alc.h>
#include <map>

namespace anna {
namespace sound {

class OpenALAudioDevice : public AudioDevice {
public:
	explicit OpenALAudioDevice(
		std::map<AudioDevice::ATTRIBUTE, int> context_attributes =
		std::map<AudioDevice::ATTRIBUTE, int>())
		throw(exceptions::CreationException);
	virtual ~OpenALAudioDevice(void);
	virtual float getDopplerFactor(void) const;
	virtual void setDopplerFactor(float value);
	virtual float getSpeedOfSound(void) const;
	virtual void setSpeedOfSound(float units_per_second);
	virtual AudioDevice::DISTANCE_MODEL getDistanceModel(void) const;
	virtual void setDistanceModel(AudioDevice::DISTANCE_MODEL model);
	virtual Source* createSource(void) throw(exceptions::CreationException);
	virtual Source* takeOutSource(Source* source);
	virtual Buffer* createBuffer(void) throw(exceptions::CreationException);
	virtual Buffer* takeOutBuffer(Buffer* buffer);
	virtual void join(Buffer* buffer, Source* source)
		throw(exceptions::SettingException);

private:
	ALCdevice*  openal_device;
	ALCcontext* openal_context;
	std::map<Source*, unsigned int> sources;
	std::map<Buffer*, unsigned int> buffers;
};

}
}
#endif
