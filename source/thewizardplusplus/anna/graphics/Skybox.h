#ifndef SKYBOX_H
#define SKYBOX_H

#include "Object.h"
#include "Texture.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class Skybox : public Object {
public:
	Skybox(Texture* top, Texture* bottom, Texture* side1, Texture* side2,
		Texture* side3, Texture* side4);
};

}
}
}
#endif
