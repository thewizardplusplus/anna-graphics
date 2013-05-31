#include "anna/sound/SoundManager.h"
#include "anna/sound/Sound.h"

using namespace anna::sound;

int main(void) {
	SoundManager sound_manager;
	Sound* sound = sound_manager.createSound("helloworld.ogg");

	sound->getSource()->play();
	while (sound->getSource()->getState() == Source::PLAYING) {}
}
