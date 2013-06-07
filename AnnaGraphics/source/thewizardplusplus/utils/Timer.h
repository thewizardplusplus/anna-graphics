#ifndef TIMER_H
#define TIMER_H

#include "os.h"
#ifdef OS_LINUX
#include <sys/time.h>
#elif defined(OS_WINDOWS)
#include <windows.h>
/* Удаляю препроцессорную константу ERROR (которая определена в хедере wingdi.h,
 * который, в свою очередь, подключается в хедере windows.h), так как она мешает
 * определению и использованию перечисления thewizardplusplus::utils::
 * ConsoleMessageType ниже.
 */
#undef ERROR
#endif

namespace thewizardplusplus {
namespace utils {

class Timer {
public:
	Timer(void);
	void start(void);
	size_t getElapsedTimeInUs(void) const;

private:
	#ifdef OS_LINUX
	timeval start_time;
	#elif defined(OS_WINDOWS)
	LARGE_INTEGER frequency;
	LARGE_INTEGER start_time;
	#endif
};

}
}
#endif
