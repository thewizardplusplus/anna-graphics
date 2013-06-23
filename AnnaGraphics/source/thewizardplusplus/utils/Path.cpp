#include "Path.h"
#include <algorithm>

using namespace thewizardplusplus::utils;

Path::Path(const std::string& path) :
	path(path)
{
	#ifdef OS_LINUX
	std::replace(this->path.begin(), this->path.end(),
		PATH_SEPARATOR_IN_WINDOWS, PATH_SEPARATOR_IN_LINUX);
	#elif defined(OS_WINDOWS)
	std::replace(this->path.begin(), this->path.end(), PATH_SEPARATOR_IN_LINUX,
		PATH_SEPARATOR_IN_WINDOWS);
	#endif

	#ifdef OS_LINUX
	size_t position = this->path.find_last_of(PATH_SEPARATOR_IN_LINUX);
	#elif defined(OS_WINDOWS)
	size_t position = this->path.find_last_of(PATH_SEPARATOR_IN_WINDOWS);
	#endif
	if (position != std::string::npos) {
		path_without_filename = this->path.substr(0, position + 1);
		filename = this->path.substr(position + 1);
	} else {
		filename = this->path;
	}

	position = filename.find_last_of(FILE_SEPARATOR);
	if (position != std::string::npos) {
		filename_without_extension = filename.substr(0, position);
		file_extension = filename.substr(position + 1);
	} else {
		filename_without_extension = filename;
	}
}

std::string Path::getPath(void) const {
	return path;
}

std::string Path::getPathWithoutFilename(void) const {
	return path_without_filename;
}

std::string Path::getFilename(void) const {
	return filename;
}

std::string Path::getFilenameWithoutExtension(void) const {
	return filename_without_extension;
}

std::string Path::getFileExtension(void) const {
	return file_extension;
}
