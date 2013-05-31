#ifndef SETTINGEXCEPTION_H
#define SETTINGEXCEPTION_H

#include <stdexcept>

namespace anna {
namespace exceptions {

class SettingException : public std::runtime_error {
public:
	inline explicit SettingException(const std::string& message);
};

SettingException::SettingException(const std::string& message) :
	std::runtime_error(message)
{}

}
}
#endif
