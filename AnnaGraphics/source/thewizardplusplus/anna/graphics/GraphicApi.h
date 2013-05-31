#ifndef GRAPHICAPI_H
#define GRAPHICAPI_H

#include "Window.h"
#include "FogParameters.h"
#include "Texture.h"
#include "TextureData.h"
#include "TextureLoader.h"
#include "World.h"
#include <map>

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class GraphicApi {
public:
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
	virtual Texture* createTexture(const TextureData& texture_data) = 0;
	virtual Texture* createTexture(const std::string& file_name, TextureLoader*
		loader = NULL) = 0;
	virtual void setTexture(Texture* texture) = 0;
	virtual void clear(void) = 0;
	virtual void drawWorld(World* world) = 0;

protected:
	typedef std::map<Texture*, unsigned int> TextureMap;

	Window*                window;
	bool                   ambient_lighting;
	maths::Vector3D<float> ambient_color;
	bool                   fog_mode;
	FogParameters          fog_parameters;
	TextureMap             textures;

	virtual void processSettingAmbientColor(const maths::Vector3D<float>&
		ambient_color) = 0;
	virtual void processSettingFogParameters(const FogParameters&
		fog_parameters) = 0;
};

template<typename GraphicApiType>
GraphicApiType* GraphicApi::create(void) {
	return new GraphicApiType();
}

}
}
}
#endif
