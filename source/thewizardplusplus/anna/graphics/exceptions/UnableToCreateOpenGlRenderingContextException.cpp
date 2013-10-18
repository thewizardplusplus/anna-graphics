#include "UnableToCreateOpenGlRenderingContextException.h"

using namespace thewizardplusplus::anna::graphics::exceptions;

UnableToCreateOpenGlRenderingContextException::
	UnableToCreateOpenGlRenderingContextException(void)
:
	GraphicsException("unable to create OpenGL rendering context")
{}
