#ifndef UTILITY_H
#define UTILITY_H

#include <sys/time.h>
unsigned long getMicroSec()
{
	struct timespec tv;
	clock_gettime(CLOCK_REALTIME, &tv);
	return 1000000 * tv.tv_sec + tv.tv_nsec/1000;
}

unsigned long getMilliSec()
{
    struct timespec tv;
    clock_gettime(CLOCK_REALTIME, &tv);
    return 1000 * tv.tv_sec + tv.tv_nsec/1000000;
}

bool floatEq(float a, float b)
{
    return fabs(a - b) < 0.000001f;
}

#endif