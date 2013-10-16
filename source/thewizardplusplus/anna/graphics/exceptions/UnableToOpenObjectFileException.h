#ifndef UNABLETOOPENOBJECTFILEEXCEPTION_H
#define UNABLETOOPENOBJECTFILEEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class UnableToOpenObjectFileException : public GraphicsException {
public:
	UnableToOpenObjectFileException(const std::string& filename);
};

}
}
}
}
#endif
