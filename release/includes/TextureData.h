#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include "Vector2D.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class TextureData {
public:
	TextureData(void);
	TextureData(const void* data, const maths::Vector2D<size_t>& size, bool
		transparent = false);
	bool isValid(void) const;
	const void* getData(void) const;
	maths::Vector2D<size_t> getSize(void) const;
	bool isTransparent(void) const;
	void reset(void);

private:
	bool                    valid;
	const void*             data;
	maths::Vector2D<size_t> size;
	bool                    transparent;
};

}
}
}
#endif
