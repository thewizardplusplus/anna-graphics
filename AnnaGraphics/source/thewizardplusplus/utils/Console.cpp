#include "Console.h"
#include <iostream>

using namespace thewizardplusplus::utils;

Console Console::information(void) {
	return Console(ConsoleMessageType::INFORMATION);
}

Console Console::error(void) {
	return Console(ConsoleMessageType::FAULT);
}

Console::Console(ConsoleMessageType::Types message_type) :
	message_type(message_type)
{}

Console::~Console(void) {
	if (message_type == ConsoleMessageType::INFORMATION) {
		std::cout << message_text << std::endl;
	} else if (message_type == ConsoleMessageType::FAULT) {
		std::cerr << message_text << std::endl;
	}
}

Console& Console::operator<<(const std::string& message_text) {
	this->message_text += message_text;
	return *this;
}
