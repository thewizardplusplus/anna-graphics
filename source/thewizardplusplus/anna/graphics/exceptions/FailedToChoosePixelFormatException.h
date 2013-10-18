#ifndef FAILEDTOCHOOSEPIXELFORMATEXCEPTION_H
#define FAILEDTOCHOOSEPIXELFORMATEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class FailedToChoosePixelFormatException : public GraphicsException {
public:
	FailedToChoosePixelFormatException(void);
};

}
}
}
}
#endif
