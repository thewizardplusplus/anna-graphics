#ifndef PNGTEXTURELOADER_H
#define PNGTEXTURELOADER_H

#include "TextureLoader.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class PngTextureLoader : public TextureLoader {
public:
	virtual StringList getSupportedFormats(void) const;
	virtual TextureData load(const std::string& filename);
	virtual void free(const TextureData& data);

private:
	static const int PNG_HEADER_SIZE = 8;
};

}
}
}
#endif
