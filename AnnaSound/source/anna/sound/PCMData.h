#ifndef PCMDATA_H
#define PCMDATA_H

#include <cstdlib>

namespace anna {
namespace sound {

class PCMData {
public:
	enum BITS {
		BIT_8,
		BIT_16
	};
	enum TYPE {
		MONO,
		STEREO
	};

	inline PCMData(void);
	inline PCMData(const void* data, int size, PCMData::TYPE type,
		PCMData::BITS bits, int frequency);
	inline bool isValid(void) const;
	inline const void* getData(void) const;
	inline int getSize(void) const;
	inline PCMData::TYPE getType(void) const;
	inline PCMData::BITS getBits(void) const;
	inline int getFrequency(void) const;

private:
	bool        valid;
	const void* data;
	int         size;
	TYPE        type;
	BITS        bits;
	int         frequency;
};

PCMData::PCMData(void) :
	valid(false),
	data(NULL),
	size(0),
	type(MONO),
	bits(BIT_16),
	frequency(0)
{}

PCMData::PCMData(const void* data, int size, PCMData::TYPE type,
	PCMData::BITS bits, int frequency)
:
	valid(true),
	data(data),
	size(size),
	type(type),
	bits(bits),
	frequency(frequency)
{}

bool PCMData::isValid(void) const {
	return valid;
}

const void* PCMData::getData(void) const {
	return data;
}

int PCMData::getSize(void) const {
	return size;
}

PCMData::TYPE PCMData::getType(void) const {
	return type;
}

PCMData::BITS PCMData::getBits(void) const {
	return bits;
}

int PCMData::getFrequency(void) const {
	return frequency;
}

}
}
#endif
