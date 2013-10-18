#ifndef CANNOTFINDAPPROPRIATEPIXELFORMATEXCEPTION_H
#define CANNOTFINDAPPROPRIATEPIXELFORMATEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class CannotFindAppropriatePixelFormatException : public GraphicsException {
public:
	CannotFindAppropriatePixelFormatException(void);
};

}
}
}
}
#endif
