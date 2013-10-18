#ifndef UNABLETOREGISTERWINDOWCLASSEXCEPTION_H
#define UNABLETOREGISTERWINDOWCLASSEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class UnableToRegisterWindowClassException : public GraphicsException {
public:
	UnableToRegisterWindowClassException(void);
};

}
}
}
}
#endif
