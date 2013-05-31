#ifndef OGGLOADERCREATOR_H
#define OGGLOADERCREATOR_H

#include "LoaderCreator.h"

namespace anna {
namespace sound {

class OGGLoaderCreator : public LoaderCreator {
public:
	virtual Loader* createLoader(void);
};

}
}
#endif
