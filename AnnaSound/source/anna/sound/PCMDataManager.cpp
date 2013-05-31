#include "PCMDataManager.h"
#include <fstream>
#include <locale>

using namespace anna::sound;

PCMDataManager::~PCMDataManager(void) {
	std::map<std::string, PCMData>::const_iterator i;
	for (i = data.begin(); i != data.end(); ++i) {
		Loader* loader = links[i->first];
		loader->unload(i->second);
	}

	std::map<std::string, Loader*>::const_iterator j;
	for (j = loaders.begin(); j != loaders.end(); ++j) {
		delete j->second;
	}
}

bool PCMDataManager::isLoader(const std::string& format) const {
	return loaders.count(toUpper(format));
}

void PCMDataManager::setLoader(Loader* loader) {
	if (loader != NULL) {
		std::list<std::string> formats = loader->getSupportedFormats();
		std::list<std::string>::const_iterator i;
		for (i = formats.begin(); i != formats.end(); ++i) {
			loaders[toUpper(*i)] = loader;
		}
	}
}

PCMData PCMDataManager::load(const std::string& file_path,
	const std::string& format) throw(exceptions::ReadingException)
{
	if (data.count(file_path)) {
		return data[file_path];
	}

	std::string file_format;
	if (format != "") {
		file_format = toUpper(format);
	} else {
		unsigned long position = file_path.rfind('.');
		if (position != std::string::npos) {
			file_format = toUpper(file_path.substr(position + 1,
				file_path.length()));
		}
	}

	Loader* loader = NULL;
	if (loaders.count(file_format)) {
		loader = loaders[file_format];
	} else {
		std::string message = "anna::sound: " + file_format + " format not "
			"supported.";
		throw exceptions::ReadingException(message);
	}

	std::ifstream file;
	file.open(file_path.c_str());
	if (!file.is_open()) {
		std::string message = "anna::sound: unable to open sound file \"" +
			file_path + "\".";
		throw exceptions::ReadingException(message);
	}
	PCMData pcm_data = loader->load(file);
	data[file_path] = pcm_data;
	links[file_path] = loader;
	file.close();

	return pcm_data;
}

std::string PCMDataManager::toUpper(const std::string& string) const {
	std::string result = string;
	std::locale locale;
	for (unsigned long i = 0; i < result.length(); i++) {
		result[i] = std::toupper(result[i], locale);
	}
	return result;
}
