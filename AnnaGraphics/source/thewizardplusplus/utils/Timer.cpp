#include "Timer.h"

using namespace thewizardplusplus::utils;

Timer::Timer(void) {
	start();
}

void Timer::start(void) {
	#ifdef OS_LINUX
	gettimeofday(&start_time, NULL);
	#elif defined(OS_WINDOWS)
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start_time);
	#endif
}

size_t Timer::getElapsedTimeInUs(void) const {
	#ifdef OS_LINUX
	timeval current_time;
	gettimeofday(&current_time, NULL);
	return 1000000 * (current_time.tv_sec - start_time.tv_sec) +
		(current_time.tv_usec - start_time.tv_usec);
	#elif defined(OS_WINDOWS)
	LARGE_INTEGER current_time;
	QueryPerformanceCounter(&current_time);
	return 1000000.0 * (current_time.QuadPart - start_time.QuadPart) /
		frequency.QuadPart;
	#endif
}
