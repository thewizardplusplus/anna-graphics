#include "GraphicsException.h"

using namespace thewizardplusplus::anna::graphics::exceptions;

GraphicsException::GraphicsException(const std::string& message) :
	std::runtime_error("AnnaGraphics error: " + message + ".")
{}
