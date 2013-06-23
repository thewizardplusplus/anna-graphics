#ifndef PATH_H
#define PATH_H

#include "os.h"
#include <string>

namespace thewizardplusplus {
namespace utils {

class Path {
public:
	static const char PATH_SEPARATOR_IN_LINUX =   '/';
	static const char PATH_SEPARATOR_IN_WINDOWS = '\\';
	static const char FILE_SEPARATOR =            '.';

	Path(const std::string& path);
	std::string getPath(void) const;
	std::string getPathWithoutFilename(void) const;
	std::string getFilename(void) const;
	std::string getFilenameWithoutExtension(void) const;
	std::string getFileExtension(void) const;

private:
	std::string path;
	std::string path_without_filename;
	std::string filename;
	std::string filename_without_extension;
	std::string file_extension;
};

}
}
#endif
