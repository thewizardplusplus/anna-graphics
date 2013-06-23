#include "GraphicApi.h"
#include "../../utils/Console.h"
#include <cctype>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;
using namespace thewizardplusplus::utils;

GraphicApi::GraphicApi(void) :
	window(NULL),
	ambient_lighting(false),
	fog_mode(false)
{}

GraphicApi::~GraphicApi(void) {
	TextureLoaderMap::iterator i = loaders.begin();
	for (; i != loaders.end(); ++i) {
		delete i->second;
		i->second = NULL;
	}

	delete window;
	window = NULL;
}

Window* GraphicApi::getWindow(void) const {
	return window;
}

bool GraphicApi::isAmbientLighting(void) const {
	return ambient_lighting;
}

void GraphicApi::setAmbientLighting(bool ambient_lighting) {
	this->ambient_lighting = ambient_lighting;
}

Vector3D<float> GraphicApi::getAmbientColor(void) const {
	return ambient_color;
}

void GraphicApi::setAmbientColor(const Vector3D<float>& ambient_color) {
	this->ambient_color = ambient_color;
	processSettingAmbientColor(ambient_color);
}

bool GraphicApi::isFogMode(void) const {
	return fog_mode;
}

void GraphicApi::setFogMode(bool fog_mode) {
	this->fog_mode = fog_mode;
}

FogParameters GraphicApi::getFogParameters(void) const {
	return fog_parameters;
}

void GraphicApi::setFogParameters(const FogParameters& fog_parameters) {
	this->fog_parameters = fog_parameters;
	processSettingFogParameters(fog_parameters);
}

bool GraphicApi::isTextureLoader(const std::string& format) const {
	return loaders.count(toUpper(format)) ? true : false;
}

GraphicApi::StringList GraphicApi::getSupportedTextureFormats(void) const {
	StringList formats;
	TextureLoaderMap::const_iterator i = loaders.begin();
	for (; i != loaders.end(); ++i) {
		formats.push_back(i->first);
	}

	return formats;
}

TextureLoader* GraphicApi::getTextureLoader(const std::string& format) {
	if (loaders.count(format) == 1) {
		return loaders[format];
	} else {
		return NULL;
	}
}

void GraphicApi::addTextureLoader(TextureLoader* loader) {
	if (loader == NULL) {
		return;
	}

	TextureLoader::StringList formats = loader->getSupportedFormats();
	TextureLoader::StringList::const_iterator i = formats.begin();
	for (; i != formats.end(); ++i) {
		loaders[toUpper(*i)] = loader;
	}
}

void GraphicApi::removeTextureLoader(TextureLoader* loader) {
	if (loader == NULL) {
		return;
	}

	TextureLoader::StringList formats = loader->getSupportedFormats();
	TextureLoader::StringList::const_iterator i = formats.begin();
	for (; i != formats.end(); ++i) {
		removeTextureLoader(*i);
	}
}

void GraphicApi::removeTextureLoader(const std::string& format) {
	loaders.erase(toUpper(format));
}

Texture* GraphicApi::createTexture(const std::string& filename, const std::
	string& format)
{
	TextureMap::const_iterator i = textures.begin();
	for (; i != textures.end(); ++i) {
		Texture* texture = i->first;
		if (texture->name == filename) {
			return texture;
		}
	}

	std::string file_format;
	if (!format.empty()) {
		file_format = toUpper(format);
	} else {
		size_t index = filename.rfind(FILE_EXTENSION_SEPARATOR);
		if (index != std::string::npos) {
			file_format = toUpper(filename.substr(index + 1, filename.
				length()));
		}
	}

	TextureLoader* texture_loader = NULL;
	if (loaders.count(file_format) && loaders[file_format] != NULL) {
		texture_loader = loaders[file_format];
	} else {
		Console::error() << "Warning: texture format \"" + file_format + "\" "
			"not supported.";
		return NULL;
	}

	TextureData texture_data = texture_loader->load(filename);
	if (!texture_data.isValid()) {
		Console::error() << "Warning: unable to load texture file \"" + filename
			+ "\".";
		return NULL;
	}

	Texture* texture = createTexture(texture_data, filename);
	texture_loader->free(texture_data);

	return texture;
}

void GraphicApi::drawWorld(World* world) {
	if (world == NULL) {
		return;
	}

	setCamera(world->getCamera());
	for (size_t i = 0; i < world->getNumberOfOpaqueMeshes(); i++) {
		drawMesh(world->getOpaqueMesh(i));
	}

	setBlendingMode(true);
	world->sortTransparentMeshes();
	for (size_t i = 0; i < world->getNumberOfTransparentMeshes(); i++) {
		drawMesh(world->getTransparentMesh(i));
	}
	setBlendingMode(false);
}

std::string GraphicApi::toUpper(const std::string& string) const {
	std::string result = string;
	for (size_t i = 0; i < result.length(); i++) {
		result[i] = std::toupper(result[i]);
	}

	return result;
}
