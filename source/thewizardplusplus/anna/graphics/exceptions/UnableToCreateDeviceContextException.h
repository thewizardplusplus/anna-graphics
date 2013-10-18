#ifndef UNABLETOCREATEDEVICECONTEXTEXCEPTION_H
#define UNABLETOCREATEDEVICECONTEXTEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class UnableToCreateDeviceContextException : public GraphicsException {
public:
	UnableToCreateDeviceContextException(void);
};

}
}
}
}
#endif
