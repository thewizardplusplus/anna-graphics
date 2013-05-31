#include "OpenALBuffer.h"
#include "AudioDevice.h"

using namespace anna::sound;

OpenALBuffer::OpenALBuffer(OpenALAudioDevice* audio_device,
	unsigned int openal_buffer)
:
	audio_device(audio_device),
	openal_buffer(openal_buffer),
	size(0),
	type(PCMData::MONO),
	bits(PCMData::BIT_16),
	frequency(0)
{
	alGetBufferi(openal_buffer, AL_SIZE, &size);
	int channels = 1;
	alGetBufferi(openal_buffer, AL_CHANNELS, &channels);
	if (channels == 2) {
		type = PCMData::STEREO;
	}
	int bits = 16;
	alGetBufferi(openal_buffer, AL_BITS, &bits);
	if (bits == 8) {
		this->bits = PCMData::BIT_8;
	}
	alGetBufferi(openal_buffer, AL_FREQUENCY, &frequency);
}

OpenALBuffer::~OpenALBuffer(void) {
	audio_device->takeOutBuffer(this);
	alDeleteBuffers(1, &openal_buffer);
}

void OpenALBuffer::setData(const PCMData& data)
	throw(exceptions::SettingException)
{
	if (!data.isValid()) {
		return;
	}

	size =      data.getSize();
	type =      data.getType();
	bits =      data.getBits();
	frequency = data.getFrequency();

	int format = AL_FORMAT_MONO16;
	if (type == PCMData::MONO) {
		if (bits == PCMData::BIT_8) {
			format = AL_FORMAT_MONO8;
		}
	} else {
		if (bits == PCMData::BIT_8) {
			format = AL_FORMAT_STEREO8;
		} else {
			format = AL_FORMAT_STEREO16;
		}
	}

	alBufferData(openal_buffer, format, data.getData(), size, frequency);
	if (alGetError() != AL_NO_ERROR) {
		throw exceptions::SettingException("anna::sound: unable to set data to "
			"OpenAL buffer.");
	}
}
