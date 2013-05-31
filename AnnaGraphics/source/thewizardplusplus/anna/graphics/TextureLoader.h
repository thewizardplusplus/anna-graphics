#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "TextureData.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class TextureLoader {
public:
	virtual ~TextureLoader(void);
	virtual TextureData load(std::istream& source) = 0;
	virtual void free(const TextureData& data) = 0;
};

}
}
}
#endif
