#ifndef LOADERCREATOR_H
#define LOADERCREATOR_H

#include "Loader.h"

namespace anna {
namespace sound {

class LoaderCreator {
public:
	inline virtual ~LoaderCreator(void);
	virtual Loader* createLoader(void) = 0;
};

LoaderCreator::~LoaderCreator(void) {}

}
}
#endif
