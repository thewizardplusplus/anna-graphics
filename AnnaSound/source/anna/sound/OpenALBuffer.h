#ifndef OPENALBUFFER_H
#define OPENALBUFFER_H

#include "Buffer.h"
#include "OpenALAudioDevice.h"
#include <AL/al.h>

namespace anna {
namespace sound {

class OpenALBuffer : public Buffer {
public:
	OpenALBuffer(OpenALAudioDevice* audio_device, unsigned int openal_buffer);
	virtual ~OpenALBuffer(void);
	inline virtual int getSize(void) const;
	inline virtual PCMData::TYPE getType(void) const;
	inline virtual PCMData::BITS getBits(void) const;
	inline virtual int getFrequency(void) const;
	virtual void setData(const PCMData& data)
		throw(exceptions::SettingException);

private:
	OpenALAudioDevice* audio_device;
	unsigned int       openal_buffer;
	int                size;
	PCMData::TYPE      type;
	PCMData::BITS      bits;
	int                frequency;
};

int OpenALBuffer::getSize(void) const {
	return size;
}

PCMData::TYPE OpenALBuffer::getType(void) const {
	return type;
}

PCMData::BITS OpenALBuffer::getBits(void) const {
	return bits;
}

int OpenALBuffer::getFrequency(void) const {
	return frequency;
}

}
}
#endif
