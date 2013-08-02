#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class Texture {
public:
	std::string name;

	explicit Texture(const std::string& name);
};

}
}
}
#endif
