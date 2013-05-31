#ifndef SOUND_H
#define SOUND_H

#include "SoundManager.h"
#include "Source.h"
#include "Buffer.h"
#include <stdexcept>

namespace anna {
namespace sound {

class Sound {
public:
	inline Sound(SoundManager* manager, Source* source, Buffer* buffer)
		throw(std::invalid_argument);
	inline ~Sound(void);
	inline Source* getSource(void) const;
	inline Buffer* getBuffer(void) const;

private:
	SoundManager* manager;
	Source*       source;
	Buffer*       buffer;
};

Sound::Sound(SoundManager* manager, Source* source, Buffer* buffer)
	throw(std::invalid_argument)
:
	manager(manager),
	source(source),
	buffer(buffer)
{
	if (manager == NULL || source == NULL || buffer == NULL) {
		throw std::invalid_argument("anna::sound: unable to create sound with "
			"NULL sound manager, NULL source or NULL buffer.");
	}
}

Sound::~Sound(void) {
	manager->takeOutSound(this);
}

Source* Sound::getSource(void) const {
	return source;
}

Buffer* Sound::getBuffer(void) const {
	return buffer;
}

}
}
#endif
