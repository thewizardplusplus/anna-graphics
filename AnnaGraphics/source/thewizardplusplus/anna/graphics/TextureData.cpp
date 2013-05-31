#include "TextureData.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

TextureData::TextureData(void) :
	valid(false),
	data(NULL),
	transparent(false)
{}

TextureData::TextureData(const void* data, const Vector2D<size_t>& size, bool
	transparent)
:
	valid(true),
	data(data),
	size(size),
	transparent(transparent)
{}

bool TextureData::isValid(void) const {
	return valid;
}

const void* TextureData::getData(void) const {
	return data;
}

Vector2D<size_t> TextureData::getSize(void) const {
	return size;
}

bool TextureData::isTransparent(void) const {
	return transparent;
}
