#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include "TransparentType.h"

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class Material {
public:
	Texture*               texture;
	TransparentType::Types transparent_type;
	bool                   allow_ambient_light;
	bool                   allow_fog;

	Material(Texture* texture = NULL, TransparentType::Types transparent_type =
		TransparentType::NONE, bool allow_ambient_light = true, bool allow_fog
		= true);
};

}
}
}
#endif
