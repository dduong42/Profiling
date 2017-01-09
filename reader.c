#include <stdio.h>
#include <string.h>
#include "profiler.h"

void						read_malloc(char *path)
{
	FILE					*handler;
	struct s_malloc_data	s;

	if ((handler = fopen(path, "r")) == NULL) {
		perror("fopen");
		exit(1);
	}
	while (fread(&s, sizeof(s), 1, handler) == 1)
	{
		printf("ptr: %p size: %ld\n", s.ptr, s.size);
	}
	fclose(handler);
}

void		read_free(char *path)
{
	FILE	*handler;
	void	*ptr;

	if ((handler = fopen(path, "r")) == NULL) {
		perror("fopen");
		exit(1);
	}
	while (fread(&ptr, sizeof(ptr), 1, handler) == 1)
		printf("ptr: %p\n", ptr);
	fclose(handler);
}

void	usage()
{
	fprintf(stderr, "Usage: reader (malloc|free) <log_file>\n");
	exit(1);
}

int		main(int ac, char **av)
{
	if (ac < 3)
		usage();
	if (!strcmp(av[1], "malloc"))
		read_malloc(av[2]);
	else if (!strcmp(av[1], "free"))
		read_free(av[2]);
	else
		usage();
	return (0);
}
