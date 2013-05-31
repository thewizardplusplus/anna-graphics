#ifndef READINGEXCEPTION_H
#define READINGEXCEPTION_H

#include <stdexcept>

namespace anna {
namespace exceptions {

class ReadingException : public std::runtime_error {
public:
	inline explicit ReadingException(const std::string& message);
};

ReadingException::ReadingException(const std::string& message) :
	std::runtime_error(message)
{}

}
}
#endif
