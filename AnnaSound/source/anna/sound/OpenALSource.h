#ifndef OPENALSOURCE_H
#define OPENALSOURCE_H

#include "Source.h"
#include "OpenALAudioDevice.h"
#include <AL/al.h>

namespace anna {
namespace sound {

class OpenALSource : public Source {
public:
	OpenALSource(OpenALAudioDevice* audio_device, unsigned int openal_source);
	virtual ~OpenALSource(void);
	inline virtual maths::Vector3D<float> getPosition(void) const;
	inline virtual void setPosition(const maths::Vector3D<float>& position);
	inline virtual maths::Vector3D<float> getVelocity(void) const;
	inline virtual void setVelocity(const maths::Vector3D<float>& velocity);
	inline virtual maths::Vector3D<float> getDirection(void) const;
	inline virtual void setDirection(const maths::Vector3D<float>& direction);
	inline virtual float getConeInnerAngle(void) const;
	inline virtual void setConeInnerAngle(float angle_in_degrees);
	inline virtual float getConeOuterAngle(void) const;
	inline virtual void setConeOuterAngle(float angle_in_degrees);
	inline virtual float getGain(void) const;
	inline virtual void setGain(float gain);
	inline virtual float getConeOuterGain(void) const;
	inline virtual void setConeOuterGain(float gain);
	inline virtual float getMinimalGain(void) const;
	inline virtual void setMinimalGain(float minimal_gain);
	inline virtual float getMaximalGain(void) const;
	inline virtual void setMaximalGain(float maximal_gain);
	inline virtual float getReferenceDistance(void) const;
	inline virtual void setReferenceDistance(float reference_distance);
	inline virtual float getRolloffFactor(void) const;
	inline virtual void setRolloffFactor(float rolloff_factor);
	inline virtual float getMaximalDistance(void) const;
	inline virtual void setMaximalDistance(float maximal_distance);
	inline virtual float getPitch(void) const;
	inline virtual void setPitch(float pitch);
	inline virtual bool getLooping(void) const;
	inline virtual void setLooping(bool looping);
	inline virtual Source::STATE getState(void) const;
	inline virtual float getOffset(Source::OFFSET_UNITS units) const;
	inline virtual void setOffset(float offset, Source::OFFSET_UNITS units);
	inline virtual void play(void);
	inline virtual void pause(void);
	inline virtual void stop(void);
	inline virtual void rewind(void);

private:
	OpenALAudioDevice*     audio_device;
	unsigned int           openal_source;
	maths::Vector3D<float> position;
	maths::Vector3D<float> velocity;
	maths::Vector3D<float> direction;
	float                  cone_inner_angle;
	float                  cone_outer_angle;
	float                  gain;
	float                  cone_outer_gain;
	float                  minimal_gain;
	float                  maximal_gain;
	float                  reference_distance;
	float                  rolloff_factor;
	float                  maximal_distance;
	float                  pitch;
	bool                   looping;
};

maths::Vector3D<float> OpenALSource::getPosition(void) const {
	return position;
}

void OpenALSource::setPosition(const maths::Vector3D<float>& position) {
	this->position = position;
	alSource3f(openal_source, AL_POSITION, position.x, position.z, -position.y);
}

maths::Vector3D<float> OpenALSource::getVelocity(void) const {
	return velocity;
}

void OpenALSource::setVelocity(const maths::Vector3D<float>& velocity) {
	this->velocity = velocity;
	alSource3f(openal_source, AL_VELOCITY, velocity.x, velocity.z, -velocity.y);
}

maths::Vector3D<float> OpenALSource::getDirection(void) const {
	return direction;
}

void OpenALSource::setDirection(const maths::Vector3D<float>& direction) {
	this->direction = direction;
	alSource3f(openal_source, AL_DIRECTION, direction.x, direction.z,
		-direction.y);
}

float OpenALSource::getConeInnerAngle(void) const {
	return cone_inner_angle;
}

void OpenALSource::setConeInnerAngle(float angle_in_degrees) {
	cone_inner_angle = angle_in_degrees;
	alSourcef(openal_source, AL_CONE_INNER_ANGLE, angle_in_degrees);
}

float OpenALSource::getConeOuterAngle(void) const {
	return cone_outer_angle;
}

void OpenALSource::setConeOuterAngle(float angle_in_degrees) {
	cone_outer_angle = angle_in_degrees;
	alSourcef(openal_source, AL_CONE_OUTER_ANGLE, angle_in_degrees);
}

float OpenALSource::getGain(void) const {
	return gain;
}

void OpenALSource::setGain(float gain) {
	this->gain = gain;
	alSourcei(openal_source, AL_GAIN, gain);
}

float OpenALSource::getConeOuterGain(void) const {
	return cone_outer_gain;
}

void OpenALSource::setConeOuterGain(float gain) {
	cone_outer_gain = gain;
	alSourcef(openal_source, AL_CONE_OUTER_GAIN, gain);
}

float OpenALSource::getMinimalGain(void) const {
	return minimal_gain;
}

void OpenALSource::setMinimalGain(float minimal_gain) {
	this->minimal_gain = minimal_gain;
	alSourcef(openal_source, AL_MIN_GAIN, minimal_gain);
}

float OpenALSource::getMaximalGain(void) const {
	return maximal_gain;
}

void OpenALSource::setMaximalGain(float maximal_gain) {
	this->maximal_gain = maximal_gain;
	alSourcef(openal_source, AL_MAX_GAIN, maximal_gain);
}

float OpenALSource::getReferenceDistance(void) const {
	return reference_distance;
}

void OpenALSource::setReferenceDistance(float reference_distance) {
	this->reference_distance = reference_distance;
	alSourcef(openal_source, AL_REFERENCE_DISTANCE, reference_distance);
}

float OpenALSource::getRolloffFactor(void) const {
	return rolloff_factor;
}

void OpenALSource::setRolloffFactor(float rolloff_factor) {
	this->rolloff_factor = rolloff_factor;
	alSourcef(openal_source, AL_ROLLOFF_FACTOR, rolloff_factor);
}

float OpenALSource::getMaximalDistance(void) const {
	return maximal_distance;
}

void OpenALSource::setMaximalDistance(float maximal_distance) {
	this->maximal_distance = maximal_distance;
	alSourcef(openal_source, AL_MAX_DISTANCE, maximal_distance);
}

float OpenALSource::getPitch(void) const {
	return pitch;
}

void OpenALSource::setPitch(float pitch) {
	this->pitch = pitch;
	alSourcei(openal_source, AL_PITCH, pitch);
}

bool OpenALSource::getLooping(void) const {
	return looping;
}

void OpenALSource::setLooping(bool looping) {
	this->looping = looping;
	alSourcei(openal_source, AL_LOOPING, looping);
}

Source::STATE OpenALSource::getState(void) const {
	int state = 0;
	alGetSourcei(openal_source, AL_SOURCE_STATE, &state);
	switch (state) {
	case AL_INITIAL:
		return INITIAL;
	case AL_PLAYING:
		return PLAYING;
	case AL_PAUSED:
		return PAUSED;
	case AL_STOPPED:
		return STOPPED;
	default:
		return UNKNOWN;
	}
}

float OpenALSource::getOffset(Source::OFFSET_UNITS units) const {
	float offset = 0.0f;
	switch (units) {
	case SECONDS:
		alGetSourcef(openal_source, AL_SEC_OFFSET, &offset);
		break;
	case SAMPLES:
		alGetSourcef(openal_source, AL_SAMPLE_OFFSET, &offset);
		break;
	case BYTES:
		alGetSourcef(openal_source, AL_BYTE_OFFSET, &offset);
		break;
	}
	return offset;
}

void OpenALSource::setOffset(float offset, Source::OFFSET_UNITS units) {
	switch (units) {
	case SECONDS:
		alSourcef(openal_source, AL_SEC_OFFSET, offset);
		break;
	case SAMPLES:
		alSourcef(openal_source, AL_SAMPLE_OFFSET, offset);
		break;
	case BYTES:
		alSourcef(openal_source, AL_BYTE_OFFSET, offset);
		break;
	}
}

void OpenALSource::play(void) {
	alSourcePlay(openal_source);
}

void OpenALSource::pause(void) {
	alSourcePause(openal_source);
}

void OpenALSource::stop(void) {
	alSourceStop(openal_source);
}

void OpenALSource::rewind(void) {
	alSourceRewind(openal_source);
}

}
}
#endif
