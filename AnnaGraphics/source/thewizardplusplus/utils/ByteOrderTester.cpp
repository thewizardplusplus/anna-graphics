#include "ByteOrderTester.h"

using namespace thewizardplusplus::utils;

const ByteOrderTesterHelper ByteOrderTester::BYTE_ORDER_TESTER_HELPER =
	{ByteOrderTester::MARK_BYTE};

ByteOrder::Types ByteOrderTester::test(void) {
	if (BYTE_ORDER_TESTER_HELPER.bytes[0] == MARK_BYTE) {
		return ByteOrder::LITTLE_ENDIAN;
	} else if (BYTE_ORDER_TESTER_HELPER.bytes[sizeof(ByteOrderTesterHelper::
		Number) - 1] == MARK_BYTE)
	{
		return ByteOrder::BIG_ENDIAN;
	} else {
		return ByteOrder::UNKNOWN;
	}
}
