#include "UnableToOpenObjectFileException.h"

using namespace thewizardplusplus::anna::graphics::exceptions;

UnableToOpenObjectFileException::UnableToOpenObjectFileException(const std::
	string& filename)
:
	GraphicsException("unable to open object file \"" + filename + "\"")
{}
