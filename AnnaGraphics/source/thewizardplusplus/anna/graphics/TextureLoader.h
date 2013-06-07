#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "TextureData.h"
#include <list>

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class TextureLoader {
public:
	typedef std::list<std::string> StringList;

	virtual ~TextureLoader(void);
	virtual StringList getSupportedFormats(void) const = 0;
	virtual TextureData load(const std::string& filename) = 0;
	virtual void free(TextureData& data) = 0;
};

}
}
}
#endif
