#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include <sstream>

namespace thewizardplusplus {
namespace utils {

class Converter {
public:
	template<typename ValueType>
	static const std::string toString(ValueType value);
};

template<typename ValueType>
const std::string Converter::toString(ValueType value) {
	std::ostringstream out;
	out << value;

	return out.str();
}

}
}
#endif
