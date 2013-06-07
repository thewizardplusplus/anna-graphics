#ifndef BYTEORDER_H
#define BYTEORDER_H

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
