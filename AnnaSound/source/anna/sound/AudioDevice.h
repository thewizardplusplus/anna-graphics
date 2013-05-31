#ifndef AUDIODEVICE_H
#define AUDIODEVICE_H

#include "../exceptions/CreationException.h"
#include "Listener.h"
#include "Source.h"
#include "Buffer.h"
#include "../exceptions/SettingException.h"

namespace anna {
namespace sound {

class AudioDevice {
public:
	enum ATTRIBUTE {
		FREQUENCY,
		REFRESH,
		SYNC,
		MONO_SOURCES,
		STEREO_SOURCES
	};
	enum DISTANCE_MODEL {
		NONE,
		LINEAR_DISTANCE,
		LINEAR_DISTANCE_CLAMPED,
		INVERSE_DISTANCE,
		INVERSE_DISTANCE_CLAMPED,
		EXPONENT_DISTANCE,
		EXPONENT_DISTANCE_CLAMPED,
		UNKNOWN
	};

	inline AudioDevice(void) throw(exceptions::CreationException);
	inline virtual ~AudioDevice(void);
	virtual float getDopplerFactor(void) const = 0;
	virtual void setDopplerFactor(float value) = 0;
	virtual float getSpeedOfSound(void) const = 0;
	virtual void setSpeedOfSound(float units_per_second) = 0;
	virtual AudioDevice::DISTANCE_MODEL getDistanceModel(void) const = 0;
	virtual void setDistanceModel(AudioDevice::DISTANCE_MODEL model) = 0;
	inline Listener* getListener(void);
	virtual Source* createSource(void) throw(exceptions::CreationException) = 0;
	virtual Source* takeOutSource(Source* source) = 0;
	virtual Buffer* createBuffer(void) throw(exceptions::CreationException) = 0;
	virtual Buffer* takeOutBuffer(Buffer* buffer) = 0;
	virtual void join(Buffer* buffer, Source* source)
		throw(exceptions::SettingException) = 0;

protected:
	Listener* listener;
};

AudioDevice::AudioDevice(void) throw(exceptions::CreationException) :
	listener(NULL)
{}

AudioDevice::~AudioDevice(void) {
	delete listener;
	listener = NULL;
}

Listener* AudioDevice::getListener(void) {
	return listener;
}

}
}
#endif
