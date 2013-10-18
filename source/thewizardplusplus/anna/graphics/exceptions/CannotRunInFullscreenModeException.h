#ifndef CANNOTRUNINFULLSCREENMODEEXCEPTION_H
#define CANNOTRUNINFULLSCREENMODEEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class CannotRunInFullscreenModeException : public GraphicsException {
public:
	CannotRunInFullscreenModeException(void);
};

}
}
}
}
#endif
