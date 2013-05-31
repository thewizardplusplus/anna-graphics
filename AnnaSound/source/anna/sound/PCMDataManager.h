#ifndef PCMDATAMANAGER_H
#define PCMDATAMANAGER_H

#include "Loader.h"
#include "PCMData.h"
#include "../exceptions/ReadingException.h"
#include <map>

namespace anna {
namespace sound {

class PCMDataManager {
public:
	~PCMDataManager(void);
	bool isLoader(const std::string& format) const;
	void setLoader(Loader* loader);
	PCMData load(const std::string& file_path, const std::string& format =
		std::string()) throw(exceptions::ReadingException);

private:
	std::map<std::string, PCMData> data;
	std::map<std::string, Loader*> loaders;
	std::map<std::string, Loader*> links;

	std::string toUpper(const std::string& string) const;
};

}
}
#endif
