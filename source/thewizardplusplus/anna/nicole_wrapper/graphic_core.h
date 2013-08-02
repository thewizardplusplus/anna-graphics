#ifndef GRAPHICCORE_H
#define GRAPHICCORE_H

#include "../graphics/OpenGlGraphicApi.h"

namespace thewizardplusplus {
namespace anna {
namespace nicole_framework {

extern anna::graphics::GraphicApi* graphic_api;

extern "C" {

void GraphicCoreOpen(void);
float GraphicCoreGetScreenWidth(void);
float GraphicCoreGetScreenHeight(void);
float GraphicCoreIsPressedKey(float key_code);
float GraphicCoreIsPressedButton(float button_code);
float GraphicCoreGetPointerPositionX(void);
float GraphicCoreGetPointerPositionY(void);
void GraphicCoreSetPointerPosition(float y, float x);
float GraphicCoreIsAmbientLighting(void);
void GraphicCoreSetAmbientLighting(float ambient_lighting);
float GraphicCoreGetAmbientColorRed(void);
float GraphicCoreGetAmbientColorGreen(void);
float GraphicCoreGetAmbientColorBlue(void);
void GraphicCoreSetAmbientColor(float blue, float green, float red);
float GraphicCoreIsFogMode(void);
void GraphicCoreSetFogMode(float fog_mode);
float GraphicCoreGetFogColorRed(void);
float GraphicCoreGetFogColorGreen(void);
float GraphicCoreGetFogColorBlue(void);
void GraphicCoreSetFogColor(float fog_color_blue, float fog_color_green, float
	fog_color_red);
float GraphicCoreGetFogDensity(void);
void GraphicCoreSetFogDensity(float fog_density);
float GraphicCoreGetFogStartDepth(void);
void GraphicCoreSetFogStartDepth(float fog_start_depth);
float GraphicCoreGetFogEndDepth(void);
void GraphicCoreSetFogEndDepth(float fog_end_depth);
void GraphicCoreClear(void);
void GraphicCoreDrawScene(float scene_id);
void GraphicCoreUpdate(void);
void GraphicCoreClose(void);

}

}
}
}
#endif
