#ifndef UNABLETOCREATEOPENGLRENDERINGCONTEXTEXCEPTION_H
#define UNABLETOCREATEOPENGLRENDERINGCONTEXTEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class UnableToCreateOpenGlRenderingContextException : public GraphicsException {
public:
	UnableToCreateOpenGlRenderingContextException(void);
};

}
}
}
}
#endif
