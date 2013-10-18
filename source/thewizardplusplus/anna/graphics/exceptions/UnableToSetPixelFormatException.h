#ifndef UNABLETOSETPIXELFORMATEXCEPTION_H
#define UNABLETOSETPIXELFORMATEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class UnableToSetPixelFormatException : public GraphicsException {
public:
	UnableToSetPixelFormatException(void);
};

}
}
}
}
#endif
