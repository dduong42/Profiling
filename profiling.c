/* Needed for RTLD_NEXT */
#define _GNU_SOURCE
#define MALLOC_LOG "malloc.log"
#define FREE_LOG "free.log"

#include <sys/types.h>
#include <sys/stat.h>
#include <aio.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include "profiler.h"

void						*malloc(size_t size) {
	struct s_malloc_data	s;
    void					*(*real_malloc)(size_t);
	static int				fd = 0;

	if (!fd)
		fd = open(MALLOC_LOG, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    s.ptr = real_malloc(size);
	s.size = size;
	write(fd, &s, sizeof(struct s_malloc_data));
    return (s.ptr);
}

void		free(void *ptr) {
    void	(*real_free)(void *);
	static int	fd = 0;

	if (!fd)
		fd = open(FREE_LOG, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(fd, &ptr, sizeof(ptr));
    real_free = dlsym(RTLD_NEXT, "free");
    return (real_free(ptr));
}
