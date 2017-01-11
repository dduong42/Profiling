/* Needed for RTLD_NEXT */
#define _GNU_SOURCE
#define LOG "memory.log"

#include <fcntl.h>
#include <dlfcn.h>
#include <unistd.h>
#include "profiling.h"

int				g_fd;

void			*malloc(size_t size)
{
	struct data	s;
    void		*(*real_malloc)(size_t);

	if (!g_fd)
		g_fd = open(LOG, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    real_malloc = dlsym(RTLD_NEXT, "malloc");
	s.time = time(NULL);
	s.type = MALLOC;
    s.ptr = real_malloc(size);
	s.size = size;
	write(g_fd, &s, sizeof(s));
    return (s.ptr);
}

void			free(void *ptr)
{
	struct data	s;
    void		(*real_free)(void *);

	if (!g_fd)
		g_fd = open(LOG, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	s.time = time(NULL);
	s.type = FREE;
	s.size = 0;
	s.ptr = ptr;
	write(g_fd, &s, sizeof(s));
    real_free = dlsym(RTLD_NEXT, "free");
    return (real_free(ptr));
}
