#include "CannotFindAppropriatePixelFormatException.h"

using namespace thewizardplusplus::anna::graphics::exceptions;

CannotFindAppropriatePixelFormatException::
	CannotFindAppropriatePixelFormatException(void)
:
	GraphicsException("can't find an appropriate pixel format")
{}
