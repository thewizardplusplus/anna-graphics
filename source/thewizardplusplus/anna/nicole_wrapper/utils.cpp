#include "utils.h"
#include <iostream>
#include <cstdlib>

using namespace thewizardplusplus::anna::nicole_framework;

extern "C" void Error(const std::string& description) {
	std::cerr << description << std::endl;
	std::exit(EXIT_FAILURE);
}
