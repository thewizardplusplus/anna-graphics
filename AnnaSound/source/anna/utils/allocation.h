#ifndef ERRORS_H
#define ERRORS_H

#include "utils.h"
#include <cstdlib>
#include <stdexcept>

#define ALLOCATION(type, pointer, constructor_arguments) \
	try { \
		pointer = new type(constructor_arguments); \
		if (pointer == NULL) { \
			std::abort(); \
		} \
	} catch (std::bad_alloc&) { \
		std::abort(); \
	}
#define ARRAY_ALLOCATION(type, pointer, array_sizes) \
	try { \
		pointer = new type[array_sizes]; \
		if (pointer == NULL) { \
			std::abort(); \
		} \
	} catch (std::bad_alloc&) { \
		std::abort(); \
	}
#define EMPTY_ARGUMENT
#endif
