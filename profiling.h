#ifndef PROFILER_H
#define PROFILER_H
#define _GNU_SOURCE
#include <stdlib.h>
#include <time.h>

enum type {
	MALLOC,
	FREE
};

struct data {
	void *ptr;
	size_t size;
	time_t time;
	enum type type;
};

#endif
