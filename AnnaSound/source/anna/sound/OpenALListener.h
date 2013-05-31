#ifndef OPENALLISTENER_H
#define OPENALLISTENER_H

#include "Listener.h"
#include <AL/al.h>

namespace anna {
namespace sound {

class OpenALListener : public Listener {
public:
	OpenALListener(void);
	inline virtual maths::Vector3D<float> getPosition(void) const;
	inline virtual void setPosition(const maths::Vector3D<float>& position);
	inline virtual maths::Vector3D<float> getForwardDirection(void) const;
	inline virtual void setForwardDirection(
		const maths::Vector3D<float>& forward_direction);
	inline virtual maths::Vector3D<float> getUpDirection(void) const;
	inline virtual void setUpDirection(
		const maths::Vector3D<float>& up_direction);
	inline virtual maths::Vector3D<float> getVelocity(void) const;
	inline virtual void setVelocity(const maths::Vector3D<float>& velocity);
	inline virtual float getGain(void) const;
	inline virtual void setGain(float gain);

private:
	maths::Vector3D<float> position;
	maths::Vector3D<float> forward_direction;
	maths::Vector3D<float> up_direction;
	maths::Vector3D<float> velocity;
	float                  gain;

	inline void setOrientation(void);
};

maths::Vector3D<float> OpenALListener::getPosition(void) const {
	return position;
}

void OpenALListener::setPosition(const maths::Vector3D<float>& position) {
	this->position = position;
	alListener3f(AL_POSITION, position.x, position.z, -position.y);
}

maths::Vector3D<float> OpenALListener::getForwardDirection(void) const {
	return forward_direction;
}

void OpenALListener::setForwardDirection(
	const maths::Vector3D<float>& forward_direction)
{
	this->forward_direction = forward_direction;
	setOrientation();
}

maths::Vector3D<float> OpenALListener::getUpDirection(void) const {
	return up_direction;
}

void OpenALListener::setUpDirection(
	const maths::Vector3D<float>& up_direction)
{
	this->up_direction = up_direction;
	setOrientation();
}

maths::Vector3D<float> OpenALListener::getVelocity(void) const {
	return velocity;
}

void OpenALListener::setVelocity(const maths::Vector3D<float>& velocity) {
	this->velocity = velocity;
	alListener3f(AL_VELOCITY, velocity.x, velocity.z, -velocity.y);
}

float OpenALListener::getGain(void) const {
	return gain;
}

void OpenALListener::setGain(float gain) {
	this->gain = gain;
	alListenerf(AL_GAIN, gain);
}

void OpenALListener::setOrientation(void) {
	float orientation[6] = {forward_direction.x, forward_direction.z,
		-forward_direction.y, up_direction.x, up_direction.z, -up_direction.y};
	alListenerfv(AL_ORIENTATION, orientation);
}

}
}
#endif
