#include "GraphicApi.h"

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

GraphicApi::GraphicApi(void) :
	window(NULL),
	ambient_lighting(false),
	fog_mode(false)
{}

GraphicApi::~GraphicApi(void) {
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

void GraphicApi::setAmbientColor(const maths::Vector3D<float>& ambient_color) {
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
