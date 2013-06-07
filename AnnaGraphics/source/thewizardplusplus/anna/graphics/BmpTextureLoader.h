#ifndef BMPTEXTURELOADER_H
#define BMPTEXTURELOADER_H

#include "TextureLoader.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class BmpTextureLoader : public TextureLoader {
public:
	virtual StringList getSupportedFormats(void) const;
	virtual TextureData load(const std::string& filename);
	virtual void free(TextureData& data);

private:
	static const size_t WORD_SIZE =        2;
	static const size_t DOUBLE_WORD_SIZE = 4;
	static const size_t LONG_SIZE =        4;

	unsigned char readByte(std::ifstream& in) const;
	unsigned int readWord(std::ifstream& in) const;
	unsigned long readDoubleWord(std::ifstream& in) const;
	long readLong(std::ifstream& in) const;
};

}
}
}
#endif
