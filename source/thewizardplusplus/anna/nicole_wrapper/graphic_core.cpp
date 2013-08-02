#include "graphic_core.h"
#include "utils.h"
#include "scene.h"

using namespace thewizardplusplus::anna::nicole_framework;
using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

GraphicApi* thewizardplusplus::anna::nicole_framework::graphic_api = NULL;

static void TestGraphicsCoreOpen(void) {
	if (graphic_api == NULL) {
		Error("First need to open a graphics core.");
	}
}

extern "C" void GraphicCoreOpen(void) {
	if (graphic_api != NULL) {
		Error("Graphics core can be opened only once.");
	}

	graphic_api = GraphicApi::create<OpenGlGraphicApi>();
}

extern "C" float GraphicCoreGetScreenWidth(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getWindow()->getSize().x;
}

extern "C" float GraphicCoreGetScreenHeight(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getWindow()->getSize().y;
}

extern "C" float GraphicCoreIsPressedKey(float key_code) {
	TestGraphicsCoreOpen();
	return graphic_api->getWindow()->isPressedKey(static_cast<KeyCode::Types>(
		key_code));
}

extern "C" float GraphicCoreIsPressedButton(float button_code) {
	TestGraphicsCoreOpen();
	return graphic_api->getWindow()->isPressedButton(static_cast<ButtonCode::
		Types>(button_code));
}

extern "C" float GraphicCoreGetPointerPositionX(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getWindow()->getPointerPosition().x;
}

extern "C" float GraphicCoreGetPointerPositionY(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getWindow()->getPointerPosition().y;
}

extern "C" void GraphicCoreSetPointerPosition(float y, float x) {
	TestGraphicsCoreOpen();
	graphic_api->getWindow()->setPointerPosition(x, y);
}

extern "C" float GraphicCoreIsAmbientLighting(void) {
	TestGraphicsCoreOpen();
	return graphic_api->isAmbientLighting();
}

extern "C" void GraphicCoreSetAmbientLighting(float ambient_lighting) {
	TestGraphicsCoreOpen();
	return graphic_api->setAmbientLighting(ambient_lighting);
}

extern "C" float GraphicCoreGetAmbientColorRed(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getAmbientColor().x;
}

extern "C" float GraphicCoreGetAmbientColorGreen(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getAmbientColor().y;
}

extern "C" float GraphicCoreGetAmbientColorBlue(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getAmbientColor().z;
}

extern "C" void GraphicCoreSetAmbientColor(float blue, float green, float red) {
	TestGraphicsCoreOpen();
	return graphic_api->setAmbientColor(red, green, blue);
}

extern "C" float GraphicCoreIsFogMode(void) {
	TestGraphicsCoreOpen();
	return graphic_api->isFogMode();
}

extern "C" void GraphicCoreSetFogMode(float fog_mode) {
	TestGraphicsCoreOpen();
	return graphic_api->setFogMode(fog_mode);
}

extern "C" float GraphicCoreGetFogColorRed(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getFogParameters().color.x;
}

extern "C" float GraphicCoreGetFogColorGreen(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getFogParameters().color.y;
}

extern "C" float GraphicCoreGetFogColorBlue(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getFogParameters().color.z;
}

extern "C" void GraphicCoreSetFogColor(float fog_color_blue, float
	fog_color_green, float fog_color_red)
{
	TestGraphicsCoreOpen();

	FogParameters fog_parameters = graphic_api->getFogParameters();
	fog_parameters.color = Vector3D<float>(fog_color_red, fog_color_green,
		fog_color_blue);
	graphic_api->setFogParameters(fog_parameters);
}

extern "C" float GraphicCoreGetFogDensity(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getFogParameters().density;
}

extern "C" void GraphicCoreSetFogDensity(float fog_density) {
	TestGraphicsCoreOpen();

	FogParameters fog_parameters = graphic_api->getFogParameters();
	fog_parameters.density = fog_density;
	graphic_api->setFogParameters(fog_parameters);
}

extern "C" float GraphicCoreGetFogStartDepth(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getFogParameters().start_depth;
}

extern "C" void GraphicCoreSetFogStartDepth(float fog_start_depth) {
	TestGraphicsCoreOpen();

	FogParameters fog_parameters = graphic_api->getFogParameters();
	fog_parameters.start_depth = fog_start_depth;
	graphic_api->setFogParameters(fog_parameters);
}

extern "C" float GraphicCoreGetFogEndDepth(void) {
	TestGraphicsCoreOpen();
	return graphic_api->getFogParameters().end_depth;
}
extern "C" void GraphicCoreSetFogEndDepth(float fog_end_depth) {
	TestGraphicsCoreOpen();

	FogParameters fog_parameters = graphic_api->getFogParameters();
	fog_parameters.end_depth = fog_end_depth;
	graphic_api->setFogParameters(fog_parameters);
}

extern "C" void GraphicCoreClear(void) {
	TestGraphicsCoreOpen();
	graphic_api->clear();
}

extern "C" void GraphicCoreDrawScene(float scene_id) {
	World* world = SceneGetById(scene_id);
	graphic_api->drawWorld(world);
}

extern "C" void GraphicCoreUpdate(void) {
	TestGraphicsCoreOpen();
	graphic_api->getWindow()->update();
}

extern "C" void GraphicCoreClose(void) {
	delete graphic_api;
	graphic_api = NULL;
}
