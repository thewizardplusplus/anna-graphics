#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

namespace thewizardplusplus {
namespace anna {
namespace nicole_framework {

template<typename Type>
std::string ConvertToString(Type value) {
	std::ostringstream out;
	out << value;

	std::string result = out.str();
	return result;
}

extern "C" void Error(const std::string& description);

}
}
}
#endif
