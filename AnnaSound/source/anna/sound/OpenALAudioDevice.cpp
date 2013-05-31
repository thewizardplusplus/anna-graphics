#include "OpenALAudioDevice.h"
#include "../utils/allocation.h"
#include "OpenALListener.h"
#include "OpenALSource.h"
#include "OpenALBuffer.h"

using namespace anna::sound;

OpenALAudioDevice::OpenALAudioDevice(
	std::map<AudioDevice::ATTRIBUTE, int> context_attributes)
	throw(exceptions::CreationException)
:
	openal_device(NULL),
	openal_context(NULL)
{
	openal_device = alcOpenDevice(NULL);
	if (openal_device == NULL) {
		throw exceptions::CreationException("anna::sound: unable to open "
			"OpenAL device.");
	}

	int* attributes = NULL;
	if (context_attributes.size()) {
		ARRAY_ALLOCATION(int, attributes, context_attributes.size() * 2 + 1);

		std::map<AudioDevice::ATTRIBUTE, int>::const_iterator i;
		int j = 0;
		for (i = context_attributes.begin(); i != context_attributes.end();
			++i)
		{
			switch (i->first) {
			case AudioDevice::FREQUENCY:
				attributes[j] = ALC_FREQUENCY;
				break;
			case AudioDevice::REFRESH:
				attributes[j] = ALC_REFRESH;
				break;
			case AudioDevice::SYNC:
				attributes[j] = ALC_SYNC;
				break;
			case AudioDevice::MONO_SOURCES:
				attributes[j] = ALC_MONO_SOURCES;
				break;
			case AudioDevice::STEREO_SOURCES:
				attributes[j] = ALC_STEREO_SOURCES;
				break;
			}
			j++;

			attributes[j] = i->second;
			j++;
		}

		attributes[j] = 0;
	}

	openal_context = alcCreateContext(openal_device, attributes);
	delete[] attributes;
	attributes = NULL;
	if (openal_context == NULL) {
		throw exceptions::CreationException("anna::sound: unable to create "
			"OpenAL context.");
	}
	alcMakeContextCurrent(openal_context);

	ALLOCATION(OpenALListener, listener, EMPTY_ARGUMENT);
}

OpenALAudioDevice::~OpenALAudioDevice(void) {
	std::map<Source*, unsigned int>::const_iterator i = sources.begin();
	while (i != sources.end()) {
		delete i->first;
		i = sources.begin();
	}

	std::map<Buffer*, unsigned int>::const_iterator j = buffers.begin();
	while (j != buffers.end()) {
		delete j->first;
		j = buffers.begin();
	}

	alcMakeContextCurrent(NULL);
	alcDestroyContext(openal_context);
	openal_context = NULL;
	alcCloseDevice(openal_device);
	openal_device = NULL;
}

float OpenALAudioDevice::getDopplerFactor(void) const {
	return alGetFloat(AL_DOPPLER_FACTOR);
}

void OpenALAudioDevice::setDopplerFactor(float value) {
	alDopplerFactor(value);
}

float OpenALAudioDevice::getSpeedOfSound(void) const {
	return alGetFloat(AL_SPEED_OF_SOUND);
}

void OpenALAudioDevice::setSpeedOfSound(float units_per_second) {
	alSpeedOfSound(units_per_second);
}

AudioDevice::DISTANCE_MODEL OpenALAudioDevice::getDistanceModel(void) const {
	switch (alGetInteger(AL_DISTANCE_MODEL)) {
	case AL_NONE:
		return NONE;
	case AL_LINEAR_DISTANCE:
		return LINEAR_DISTANCE;
	case AL_LINEAR_DISTANCE_CLAMPED:
		return LINEAR_DISTANCE_CLAMPED;
	case AL_INVERSE_DISTANCE:
		return INVERSE_DISTANCE;
	case AL_INVERSE_DISTANCE_CLAMPED:
		return INVERSE_DISTANCE_CLAMPED;
	case AL_EXPONENT_DISTANCE:
		return EXPONENT_DISTANCE;
	case AL_EXPONENT_DISTANCE_CLAMPED:
		return EXPONENT_DISTANCE_CLAMPED;
	default:
		return UNKNOWN;
	}
}

void OpenALAudioDevice::setDistanceModel(AudioDevice::DISTANCE_MODEL model) {
	switch (model) {
	case NONE:
		alDistanceModel(AL_NONE);
		break;
	case LINEAR_DISTANCE:
		alDistanceModel(AL_LINEAR_DISTANCE);
		break;
	case LINEAR_DISTANCE_CLAMPED:
		alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
		break;
	case INVERSE_DISTANCE:
		alDistanceModel(AL_INVERSE_DISTANCE);
		break;
	case UNKNOWN:
	case INVERSE_DISTANCE_CLAMPED:
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
		break;
	case EXPONENT_DISTANCE:
		alDistanceModel(AL_EXPONENT_DISTANCE);
		break;
	case EXPONENT_DISTANCE_CLAMPED:
		alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
		break;
	}
}

Source* OpenALAudioDevice::createSource(void)
	throw(exceptions::CreationException)
{
	unsigned int openal_source = 0;
	alGenSources(1, &openal_source);
	if (alGetError() != AL_NO_ERROR) {
		throw exceptions::CreationException("anna::sound: unable to create "
			"OpenAL source.");
	}

	Source* source = NULL;
	ALLOCATION(OpenALSource, source, UNION_ARGUMENTS(this, openal_source));

	sources[source] = openal_source;

	return source;
}

Source* OpenALAudioDevice::takeOutSource(Source* source) {
	if (sources.count(source)) {
		sources.erase(source);
	}
	return source;
}

Buffer* OpenALAudioDevice::createBuffer(void)
	throw(exceptions::CreationException)
{
	unsigned int openal_buffer = 0;
	alGenBuffers(1, &openal_buffer);
	if (alGetError() != AL_NO_ERROR) {
		throw exceptions::CreationException("anna::sound: unable to create "
			"OpenAL buffer.");
	}

	Buffer* buffer = NULL;
	ALLOCATION(OpenALBuffer, buffer, UNION_ARGUMENTS(this, openal_buffer));

	buffers[buffer] = openal_buffer;

	return buffer;
}

Buffer* OpenALAudioDevice::takeOutBuffer(Buffer* buffer) {
	if (buffers.count(buffer)) {
		buffers.erase(buffer);
	}
	return buffer;
}

void OpenALAudioDevice::join(Buffer* buffer, Source* source)
	throw(exceptions::SettingException)
{
	if (buffers.count(buffer) && sources.count(source)) {
		alSourcei(sources[source], AL_BUFFER, buffers[buffer]);
	} else if (buffer == NULL && sources.count(source)) {
		alSourcei(sources[source], AL_BUFFER, 0);
	} else {
		return;
	}
	if (alGetError() != AL_NO_ERROR) {
		throw exceptions::SettingException("anna::sound: unable to set OpenAL "
			"buffer to OpenAL source.");
	}
}
