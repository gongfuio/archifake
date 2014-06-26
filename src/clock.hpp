#ifndef __CLOCK_H_INCLUDE__
#define __CLOCK_H_INCLUDE__


#include <memory.h>
#include <sys/stat.h>


class Clock {
protected:
	static double frequencyScale;


public:
	static void setup() {
		struct timespec ts;

		memset(&ts, 0, sizeof(struct timespec));
		clock_getres(CLOCK_MONOTONIC, &ts);
		Clock::frequencyScale = 1.0 / (double)(((unsigned long long)ts.tv_sec + (unsigned long long)ts.tv_nsec) * 1000l * 1000l * 1000l);
	}


	static unsigned long long tick() {
		struct timespec ts;

		memset(&ts, 0, sizeof(struct timespec));
		clock_gettime(CLOCK_MONOTONIC, &ts);
		return ((unsigned long long)ts.tv_sec * 1000l * 1000l * 1000l + (unsigned long long)ts.tv_nsec);
	}

	static double elapsed(unsigned long long lastTick) {
		return (double)(Clock::tick() - lastTick) * Clock::frequencyScale;
	}
};


#endif //__CLOCK_H_INCLUDE__