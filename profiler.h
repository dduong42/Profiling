#ifndef PROFILER_H
# define PROFILER_H
# define _GNU_SOURCE
# include <stdlib.h>

struct		s_malloc_data
{
	void	*ptr;
	size_t	size;
};

#endif
