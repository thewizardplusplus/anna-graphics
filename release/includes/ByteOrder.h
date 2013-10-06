#ifndef BYTEORDER_H
#define BYTEORDER_H

#include "os.h"
#ifdef OS_LINUX
/* Удаляю препроцессорную константу LITTLE_ENDIAN (которая определена где-то в
 * libc для Linux), так как она мешает определению и использованию перечисления
 * thewizardplusplus::utils::ByteOrder ниже.
 * Проверить компиляцию на платформе big-endian возможности нету, поэтому на
 * всякий случай удаляю препроцессорную константу BIG_ENDIAN, если такая вдруг
 * определена. По той же причине.
 */
#undef LITTLE_ENDIAN
#undef BIG_ENDIAN
#endif

namespace thewizardplusplus {
namespace utils {

class ByteOrder {
public:
	enum Types {
		UNKNOWN,
		LITTLE_ENDIAN,
		BIG_ENDIAN
	};
};

}
}
#endif
