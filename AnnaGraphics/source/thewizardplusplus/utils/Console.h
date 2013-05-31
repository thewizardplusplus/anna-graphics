#ifndef CONSOLE_H
#define CONSOLE_H

#include "ConsoleMessageType.h"
#include <string>

namespace thewizardplusplus {
namespace utils {

class Console {
public:
	static Console information(void);
	static Console error(void);

	Console(ConsoleMessageType::Types message_type);
	~Console(void);
	Console& operator<<(const std::string& message_text);

private:
	ConsoleMessageType::Types message_type;
	std::string               message_text;
};

}
}
#endif
