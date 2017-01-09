LIB = profiling.so
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIB = profiling.so
NAME = my_program
READER = reader
RM = rm -f

.PHONY: clean

all: $(LIB) $(NAME) $(READER)

$(NAME): main.c
	$(CC) $< -o $@

$(LIB): profiling.c profiler.h
	$(CC) $(CFLAGS) -include profiler.h -shared -fPIC -o $@ $< -ldl -lrt

$(READER): reader.c profiler.h
	$(CC) $(CFLAGS) -include profiler.h $< -o $@

clean:
	$(RM) $(LIB) $(NAME) $(READER) malloc.log free.log