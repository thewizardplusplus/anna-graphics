#ifndef CREATIONEXCEPTION_H
#define CREATIONEXCEPTION_H

#include <stdexcept>

namespace anna {
namespace exceptions {

class CreationException : public std::runtime_error {
public:
	inline explicit CreationException(const std::string& message);
};

CreationException::CreationException(const std::string& message) :
	std::runtime_error(message)
{}

}
}
#endif
