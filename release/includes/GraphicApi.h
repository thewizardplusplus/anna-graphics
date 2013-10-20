#ifndef GRAPHICAPI_H
#define GRAPHICAPI_H

#include <Window.h>
#include <FogParameters.h>
#include <Texture.h>
#include <TextureData.h>
#include <TextureLoader.h>
#include <World.h>
#include <map>

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class GraphicApi {
public:
	typedef std::list<std::string> StringList;

	template<typename GraphicApiType>
	static GraphicApiType* create(void);

	GraphicApi(void);
	virtual ~GraphicApi(void);
	Window* getWindow(void) const;
	bool isAmbientLighting(void) const;
	void setAmbientLighting(bool ambient_lighting);
	maths::Vector3D<float> getAmbientColor(void) const;
	void setAmbientColor(const maths::Vector3D<float>& ambient_color);
	void setAmbientColor(float red, float green, float blue);
	bool isFogMode(void) const;
	void setFogMode(bool fog_mode);
	FogParameters getFogParameters(void) const;
	void setFogParameters(const FogParameters& fog_parameters);
	bool isTextureLoader(const std::string& format) const;
	StringList getSupportedTextureFormats(void) const;
	TextureLoader* getTextureLoader(const std::string& format);
	void addTextureLoader(TextureLoader* loader);
	void removeTextureLoader(TextureLoader* loader);
	void removeTextureLoader(const std::string& format);
	virtual Texture* createTexture(const TextureData& texture_data, const
		std::string& name = std::string()) = 0;
	Texture* createTexture(const std::string& filename, const std::string&
		format = std::string());
	virtual void setTexture(Texture* texture) = 0;
	virtual void clear(void) = 0;
	void drawWorld(World* world);

protected:
	typedef std::map<Texture*, unsigned int>      TextureMap;
	typedef std::map<std::string, TextureLoader*> TextureLoaderMap;

	Window*                window;
	bool                   ambient_lighting;
	maths::Vector3D<float> ambient_color;
	bool                   fog_mode;
	FogParameters          fog_parameters;
	TextureMap             textures;
	TextureLoaderMap       loaders;

	virtual void processSettingAmbientColor(const maths::Vector3D<float>&
		ambient_color) = 0;
	virtual void processSettingFogParameters(const FogParameters&
		fog_parameters) = 0;
	virtual void setBlendingMode(bool blending_mode) = 0;
	virtual void setCamera(Camera* camera) = 0;
	virtual void drawMesh(Mesh* mesh) = 0;
	std::string toUpper(const std::string& string) const;

private:
	static const char FILE_EXTENSION_SEPARATOR = '.';
};

template<typename GraphicApiType>
GraphicApiType* GraphicApi::create(void) {
	GraphicApiType* gapi = new GraphicApiType();
	gapi->setAmbientColor(1.0f, 1.0f, 1.0f);
	gapi->setFogParameters(FogParameters());

	return gapi;
}

}
}
}
#endif
