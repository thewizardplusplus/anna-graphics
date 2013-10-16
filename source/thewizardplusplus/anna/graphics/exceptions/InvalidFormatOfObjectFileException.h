#ifndef INVALIDFORMATOFOBJECTFILEEXCEPTION_H
#define INVALIDFORMATOFOBJECTFILEEXCEPTION_H

#include "GraphicsException.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class InvalidFormatOfObjectFileException : public GraphicsException {
public:
	InvalidFormatOfObjectFileException(const std::string& filename, const std::
		string& error_description);
};

}
}
}
}
#endif
