#include "OpenALListener.h"

using namespace anna::sound;

OpenALListener::OpenALListener(void) :
	gain(1.0f)
{
	alGetListener3f(AL_POSITION, &position.x, &position.z, &position.y);
	position.y = -position.y;

	float orientation[6] = {0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f};
	alGetListenerfv(AL_ORIENTATION, orientation);
	forward_direction.x = orientation[0];
	forward_direction.y = -orientation[2];
	forward_direction.z = orientation[1];
	up_direction.x = orientation[3];
	up_direction.y = -orientation[5];
	up_direction.z = orientation[4];

	alGetListener3f(AL_VELOCITY, &velocity.x, &velocity.z, &velocity.y);
	velocity.y = -velocity.y;

	alGetListenerf(AL_GAIN, &gain);
}
