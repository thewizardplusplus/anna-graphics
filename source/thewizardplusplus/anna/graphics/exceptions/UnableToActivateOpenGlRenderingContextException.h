#ifndef UNABLETOACTIVATEOPENGLRENDERINGCONTEXTEXCEPTION_H
#define UNABLETOACTIVATEOPENGLRENDERINGCONTEXTEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class UnableToActivateOpenGlRenderingContextException : public GraphicsException
{
public:
	UnableToActivateOpenGlRenderingContextException(void);
};

}
}
}
}
#endif
