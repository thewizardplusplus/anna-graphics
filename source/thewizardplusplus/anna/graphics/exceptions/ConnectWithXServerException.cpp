#include "ConnectWithXServerException.h"

using namespace thewizardplusplus::anna::graphics::exceptions;

ConnectWithXServerException::ConnectWithXServerException(void) :
	GraphicsException("unable to connect with X Server")
{}
