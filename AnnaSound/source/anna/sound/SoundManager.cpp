#include "SoundManager.h"
#include "OpenALAudioDeviceCreator.h"
#include "OGGLoaderCreator.h"
#include "Sound.h"
#include "../utils/allocation.h"
#include <algorithm>

using namespace anna::sound;

SoundManager::SoundManager(
	std::map<AudioDevice::ATTRIBUTE, int> context_attributes)
	throw(exceptions::CreationException)
:
	audio_device(NULL)
{
	OpenALAudioDeviceCreator audio_device_creator;
	audio_device = audio_device_creator.createAudioDevice(context_attributes);

	OGGLoaderCreator loader_creator;
	data_manager.setLoader(loader_creator.createLoader());
}

SoundManager::~SoundManager(void) {
	std::list<Sound*>::const_iterator i = sounds.begin();
	while (i != sounds.end()) {
		delete (*i);
		i = sounds.begin();
	}

	delete audio_device;
	audio_device = NULL;
}

PCMDataManager& SoundManager::getDataManager(void) {
	return data_manager;
}

Sound* SoundManager::createSound(const std::string& file_path,
	const std::string& format) throw(exceptions::CreationException,
	exceptions::ReadingException, exceptions::SettingException,
	std::invalid_argument)
{
	Source* source = audio_device->createSource();
	Buffer* buffer = audio_device->createBuffer();
	buffer->setData(data_manager.load(file_path, format));
	audio_device->join(buffer, source);

	Sound* sound = NULL;
	ALLOCATION(Sound, sound, UNION_ARGUMENTS(this, UNION_ARGUMENTS(source,
		buffer)));
	try {
		sounds.push_back(sound);
	} catch (std::bad_alloc&) {}
	return sound;
}

Sound* SoundManager::takeOutSound(Sound* sound) {
	if (std::find(sounds.begin(), sounds.end(), sound) != sounds.end()) {
		sounds.remove(sound);
	}
	return sound;
}
