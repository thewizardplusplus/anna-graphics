#ifndef UNABLETOCREATEWINDOWEXCEPTION_H
#define UNABLETOCREATEWINDOWEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class UnableToCreateWindowException : public GraphicsException {
public:
	UnableToCreateWindowException(void);
};

}
}
}
}
#endif
