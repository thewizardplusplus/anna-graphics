#include "OGGLoaderCreator.h"
#include "../utils/allocation.h"
#include "OGGLoader.h"

using namespace anna::sound;

Loader* OGGLoaderCreator::createLoader(void) {
	Loader* loader = NULL;
	ALLOCATION(OGGLoader, loader, EMPTY_ARGUMENT);
	return loader;
}
