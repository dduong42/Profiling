#include <stdio.h>
#include <string.h>
#include <time.h>
#include "profiling.h"

int				main(int ac, char **av)
{
	FILE		*handler;
	struct data	s;
	struct tm	tm;
	char		time_s[32];

	if (ac < 2) {
		fprintf(stderr, "Usage: reader <log_file>\n");
		return (1);
	}

	if ((handler = fopen(av[1], "r")) == NULL) {
		perror("fopen");
		return (1);
	}
	while (fread(&s, sizeof(s), 1, handler) == 1)
	{
		if (localtime_r(&s.time, &tm) == NULL) {
			perror("localtime_r");
			return (1);
		}
		if (asctime_r(&tm, time_s) == NULL) {
			perror("asctime_r");
			return (1);
		}

		if (s.type == MALLOC)
			printf("%s MALLOC: ptr: %p size: %ld\n", time_s, s.ptr, s.size);
		else if (s.type == FREE)
			printf("%s FREE: ptr: %p\n", time_s, s.ptr);
		else {
			fprintf(stderr, "Wrong data, type is neither FREE nor MALLOC.\n");
			return (1);
		}
	}
	fclose(handler);
	return (0);
}
