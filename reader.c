#include <stdio.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include "profiling.h"

void usage(void)
{
	fprintf(stderr, "Usage: reader [--json] <log_file>\n");
	exit(1);
}

void print_data(struct data *s)
{
	struct tm tm;
	char time_s[32];

	if (localtime_r(&s->time, &tm) == NULL) {
		perror("localtime_r");
		exit(1);
	}
	if (asctime_r(&tm, time_s) == NULL) {
		perror("asctime_r");
		exit(1);
	}
	if (s->type == MALLOC)
		printf("%s MALLOC: ptr: %p size: %ld\n", time_s, s->ptr,
		       s->size);
	else if (s->type == FREE)
		printf("%s FREE: ptr: %p\n", time_s, s->ptr);
	else {
		fprintf(stderr,
			"Wrong data, type is neither FREE nor MALLOC.\n");
		exit(1);
	}
}

void print_data_json(struct data *s)
{
	char *str_type;

	if (s->type == MALLOC)
		str_type = "malloc";
	else if (s->type == FREE)
		str_type = "free";
	else {
		fprintf(stderr,
			"Wrong data, type is neither FREE nor MALLOC.\n");
		exit(1);
	}
	printf("{\"type\":%s,\"time\":%ld,\"ptr\":%p,\"size\":%ld}", str_type,
	       s->time, s->ptr, s->size);
}

int main(int ac, char **av)
{
	FILE *handler;
	struct data s;
	int json_flag;
	int remaining_ac;
	int c;
	struct option opts[] = {
		{"json", no_argument, &json_flag, 1},
		{0, 0, 0, 0}
	};

	json_flag = 0;
	while (1) {
		c = getopt_long(ac, av, "", opts, NULL);
		if (c == '?')
			usage();
		else if (c == -1)
			break;
	}

	remaining_ac = ac - optind;
	if (remaining_ac < 1)
		usage();

	if ((handler = fopen(av[optind], "r")) == NULL) {
		perror("fopen");
		return (1);
	}
	if (json_flag) {
		putchar('[');
		fread(&s, sizeof(s), 1, handler);
		print_data_json(&s);
		while (fread(&s, sizeof(s), 1, handler) == 1) {
			putchar(',');
			print_data_json(&s);
		}
		puts("]");
	} else {
		while (fread(&s, sizeof(s), 1, handler) == 1)
			print_data(&s);
	}
	fclose(handler);
	return (0);
}
