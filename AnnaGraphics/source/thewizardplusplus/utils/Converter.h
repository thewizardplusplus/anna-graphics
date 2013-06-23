#ifndef CONVERTER_H
#define CONVERTER_H

#include <sstream>

namespace thewizardplusplus {
namespace utils {

class Converter {
public:
	template<typename ValueType>
	static std::string toString(ValueType value);
};

template<typename ValueType>
std::string Converter::toString(ValueType value) {
	std::ostringstream out;
	out << value;

	return out.str();
}

}
}
#endif
