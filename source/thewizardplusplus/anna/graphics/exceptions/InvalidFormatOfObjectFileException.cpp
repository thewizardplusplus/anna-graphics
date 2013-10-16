#include "InvalidFormatOfObjectFileException.h"

using namespace thewizardplusplus::anna::graphics::exceptions;

InvalidFormatOfObjectFileException::InvalidFormatOfObjectFileException(const std
	::string& filename, const std::string& error_description)
:
	GraphicsException("invalid format of object file \"" + filename + "\" - " +
		error_description)
{}
