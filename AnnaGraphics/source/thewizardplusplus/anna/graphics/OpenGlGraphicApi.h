#ifndef OPENGLGRAPHICAPI_H
#define OPENGLGRAPHICAPI_H

#include "GraphicApi.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class OpenGlGraphicApi : public GraphicApi {
public:
	OpenGlGraphicApi(void);
	virtual Texture* createTexture(const TextureData& texture_data);
	virtual Texture* createTexture(const std::string& file_name, TextureLoader*
		loader = NULL);
	virtual void setTexture(Texture* texture);
	virtual void clear(void);
	virtual void drawWorld(World* world);

protected:
	virtual void processSettingAmbientColor(const maths::Vector3D<float>&
		ambient_color);
	virtual void processSettingFogParameters(const FogParameters&
		fog_parameters);

private:
	static const size_t DEFAULT_TEXTURE_SIZE =
		512;
	static const size_t DEFAULT_TEXTURE_PIECES =
		16;
	static const maths::Vector3D<unsigned char> DEFAULT_TEXTURE_LIGHT_COLOR;
	static const maths::Vector3D<unsigned char> DEFAULT_TEXTURE_DARK_COLOR;
	static const std::string                    TEXTURE_FROM_DATA_BASE_NAME;

	Texture* default_texture;
	int      last_id_texture_from_data;

	void createDefaultTexture(void);
	void setCamera(Camera* camera);
	void drawMesh(Mesh* mesh);
};

}
}
}
#endif
