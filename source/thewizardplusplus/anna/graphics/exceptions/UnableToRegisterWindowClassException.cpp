#include "UnableToRegisterWindowClassException.h"

using namespace thewizardplusplus::anna::graphics::exceptions;

UnableToRegisterWindowClassException::UnableToRegisterWindowClassException(void)
:
	GraphicsException("unable to register the window class")
{}
