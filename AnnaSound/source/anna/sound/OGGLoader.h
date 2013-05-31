#ifndef OGGLOADER_H
#define OGGLOADER_H

#include "Loader.h"

namespace anna {
namespace sound {

class OGGLoader : public Loader {
public:
	virtual std::list<std::string> getSupportedFormats(void) const;
	virtual PCMData load(std::istream& source)
		throw(exceptions::ReadingException);
	virtual void unload(const PCMData& data);
};

}
}
#endif
