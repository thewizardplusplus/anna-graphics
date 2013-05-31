#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "AudioDevice.h"
#include "PCMDataManager.h"
#include <map>
#include <list>

namespace anna {
namespace sound {

class Sound;

class SoundManager {
public:
	explicit SoundManager(
		std::map<AudioDevice::ATTRIBUTE, int> context_attributes =
		std::map<AudioDevice::ATTRIBUTE, int>())
		throw(exceptions::CreationException);
	~SoundManager(void);
	inline AudioDevice* getAudioDevice(void) const;
	PCMDataManager& getDataManager(void);
	Sound* createSound(const std::string& file_path, const std::string& format =
		std::string()) throw(exceptions::CreationException,
		exceptions::ReadingException, exceptions::SettingException,
		std::invalid_argument);
	Sound* takeOutSound(Sound* sound);

private:
	AudioDevice*      audio_device;
	PCMDataManager    data_manager;
	std::list<Sound*> sounds;
};

AudioDevice* SoundManager::getAudioDevice(void) const {
	return audio_device;
}

}
}
#endif
