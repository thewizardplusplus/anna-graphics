#ifndef BYTEORDERTESTER_H
#define BYTEORDERTESTER_H

#include "ByteOrderTesterHelper.h"
#include "ByteOrder.h"

namespace thewizardplusplus {
namespace utils {

class ByteOrderTester {
public:
	static ByteOrder::Types test(void);

private:
	static const ByteOrderTesterHelper BYTE_ORDER_TESTER_HELPER;
	static const char                  MARK_BYTE =                0x01;
};

}
}
#endif
