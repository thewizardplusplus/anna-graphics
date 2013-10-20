#ifndef GRAPHICSEXCEPTION_H
#define GRAPHICSEXCEPTION_H

#include <stdexcept>

namespace thewizardplusplus {
namespace anna {
namespace graphics {
namespace exceptions {

class GraphicsException : public std::runtime_error {
public:
	GraphicsException(const std::string& message);
};

}
}
}
}
#endif
