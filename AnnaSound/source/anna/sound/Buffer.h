#ifndef BUFFER_H
#define BUFFER_H

#include "PCMData.h"
#include "../exceptions/SettingException.h"

namespace anna {
namespace sound {

class Buffer {
public:
	inline virtual ~Buffer(void);
	virtual int getSize(void) const = 0;
	virtual PCMData::TYPE getType(void) const = 0;
	virtual PCMData::BITS getBits(void) const = 0;
	virtual int getFrequency(void) const = 0;
	virtual void setData(const PCMData& data)
		throw(exceptions::SettingException) = 0;
};

Buffer::~Buffer(void) {}

}
}
#endif
