LIB = profiling.so
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIB = profiling.so
NAME = benchmark/my_program
READER = reader
RM = rm -f

.PHONY: clean

all: $(LIB) $(NAME) $(READER)

$(NAME): benchmark/main.c
	$(CC) $< -o $@

$(LIB): profiling.c profiling.h
	$(CC) $(CFLAGS) -include profiling.h -shared -fPIC -o $@ $< -ldl -lrt

$(READER): reader.c profiling.h
	$(CC) $(CFLAGS) -include profiling.h $< -o $@

clean:
	$(RM) $(LIB) $(NAME) $(READER) memory.log
