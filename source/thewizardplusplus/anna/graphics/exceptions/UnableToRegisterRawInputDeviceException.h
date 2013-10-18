#ifndef UNABLETOREGISTERRAWINPUTDEVICEEXCEPTION_H
#define UNABLETOREGISTERRAWINPUTDEVICEEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class UnableToRegisterRawInputDeviceException : public GraphicsException {
public:
	UnableToRegisterRawInputDeviceException(void);
};

}
}
}
}
#endif
