#ifndef UTILITY_H
#define UTILITY_H

#include<sys/time.h>
unsigned long getMicroSec()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return 1000000 * tv.tv_sec + tv.tv_usec;
}

unsigned long getMilliSec()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return 1000 * tv.tv_sec + tv.tv_usec/1000;
}


#endif