#include <stdio.h>
#include <string.h>
#include "profiler.h"

int				main(int ac, char **av)
{
	FILE		*handler;
	struct data	s;

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
		if (s.type == MALLOC)
			printf("MALLOC: ptr: %p size: %ld\n", s.ptr, s.size);
		else if (s.type == FREE)
			printf("FREE: ptr: %p\n", s.ptr);
		else {
			fprintf(stderr, "Wrong data, type is neither FREE nor MALLOC.\n");
			return (1);
		}
	}
	fclose(handler);
	return (0);
}
