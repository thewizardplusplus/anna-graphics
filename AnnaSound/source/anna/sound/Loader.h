#ifndef LOADER_H
#define LOADER_H

#include "PCMData.h"
#include "../exceptions/ReadingException.h"
#include <list>
#include <istream>

namespace anna {
namespace sound {

class Loader {
public:
	inline virtual ~Loader(void);
	virtual std::list<std::string> getSupportedFormats(void) const = 0;
	virtual PCMData load(std::istream& source)
		throw(exceptions::ReadingException) = 0;
	virtual void unload(const PCMData& data) = 0;
};

Loader::~Loader(void) {}

}
}
#endif
