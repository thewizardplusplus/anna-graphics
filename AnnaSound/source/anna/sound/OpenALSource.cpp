#include "OpenALSource.h"
#include <cfloat>

using namespace anna::sound;

OpenALSource::OpenALSource(OpenALAudioDevice* audio_device,
	unsigned int openal_source)
:
	audio_device(audio_device),
	openal_source(openal_source),
	cone_inner_angle(360.0f),
	cone_outer_angle(360.0f),
	gain(1.0f),
	cone_outer_gain(0.0f),
	minimal_gain(0.0f),
	maximal_gain(1.0f),
	reference_distance(1.0f),
	rolloff_factor(1.0f),
	maximal_distance(FLT_MAX),
	pitch(1.0f),
	looping(false)
{
	alGetListener3f(AL_POSITION, &position.x, &position.z, &position.y);
	position.y = -position.y;
	alGetListener3f(AL_POSITION, &velocity.x, &velocity.z, &velocity.y);
	velocity.y = -velocity.y;
	alGetListener3f(AL_POSITION, &direction.x, &direction.z, &direction.y);
	direction.y = -direction.y;
	alGetSourcef(openal_source, AL_CONE_INNER_ANGLE, &cone_inner_angle);
	alGetSourcef(openal_source, AL_CONE_OUTER_ANGLE, &cone_outer_angle);

	alGetSourcef(openal_source, AL_GAIN, &gain);
	alGetSourcef(openal_source, AL_CONE_OUTER_GAIN, &cone_outer_gain);
	alGetSourcef(openal_source, AL_MIN_GAIN, &minimal_gain);
	alGetSourcef(openal_source, AL_MAX_GAIN, &maximal_gain);
	alGetSourcef(openal_source, AL_REFERENCE_DISTANCE, &reference_distance);
	alGetSourcef(openal_source, AL_ROLLOFF_FACTOR, &rolloff_factor);
	alGetSourcef(openal_source, AL_MAX_DISTANCE, &maximal_distance);

	alGetSourcef(openal_source, AL_PITCH, &pitch);
	int looping = 0;
	alGetSourcei(openal_source, AL_LOOPING, &looping);
	this->looping = looping;
}

OpenALSource::~OpenALSource(void) {
	audio_device->takeOutSource(this);
	alDeleteSources(1, &openal_source);
}
