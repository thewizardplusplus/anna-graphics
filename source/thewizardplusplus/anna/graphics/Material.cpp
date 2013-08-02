#include "Material.h"

using namespace thewizardplusplus::anna::graphics;

Material::Material(Texture* texture, TransparentType::Types transparent_type,
	bool allow_ambient_light, bool allow_fog)
:
	texture(texture),
	transparent_type(transparent_type),
	allow_ambient_light(allow_ambient_light),
	allow_fog(allow_fog)
{}
