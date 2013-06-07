#include "Console.h"
#include <iostream>

using namespace thewizardplusplus::utils;

Console Console::information(void) {
	return Console(ConsoleMessageType::INFORMATION);
}

Console Console::error(void) {
	return Console(ConsoleMessageType::ERROR);
}

Console::Console(ConsoleMessageType::Types message_type) :
	message_type(message_type)
{}

Console::~Console(void) {
	switch (message_type) {
		case ConsoleMessageType::ERROR:
			std::cerr << message_text << std::endl;
			break;
		case ConsoleMessageType::INFORMATION:
		default:
			std::cout << message_text << std::endl;
			break;
	}
}
