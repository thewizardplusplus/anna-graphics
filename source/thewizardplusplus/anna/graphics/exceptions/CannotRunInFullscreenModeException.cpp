#include "CannotRunInFullscreenModeException.h"

using namespace thewizardplusplus::anna::graphics::exceptions;

CannotRunInFullscreenModeException::CannotRunInFullscreenModeException(void) :
	GraphicsException("can't run in the fullscreen mode at the screen "
		"resolution on your video card")
{}
