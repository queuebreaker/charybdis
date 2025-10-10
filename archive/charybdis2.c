// ch - a password generation and management system

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <argp.h>
#include <stdlib.h>

#define error(args...) fprintf(stderr, ##args)

const char* argp_program_version = "0.1";

typedef enum
{
	WRITE,
	READ,
	DELETE
} Mode;

typedef struct
{
	bool show_help;
	bool show_usage;
	Mode mode;
	bool echo;
	bool copy;
	bool verbose;
	char* entry;
	char* vault;
	char* set;
	int length;
	char* start_with;
} Choptions;

int
argp_parse_opts(int key, char* arg, struct argp_state* state)
{
	int *arg_count = state->input;
	switch(key)
	{
		case ARGP_KEY_ARG:
			{
				
			}
			break;
		case ARGP_KEY_END:
			{
				printf("\n");
				if (*arg_count >= 1)
					argp_failure(state, 1, 0, "too few arguments");
				else if (*arg_count < 0)
					argp_failure(state, 1, 0, "too many arguments");
			}
			break;
	}
return 0;
}

struct argp_option
argp_opts[] =
{
	{"new", 'n', NULL, 0, "Register entry"},
};

struct argp
argp = {argp_opts, argp_parse_opts, 0, 0};

int
main(int argc, char** argv)
{
	Choptions options;
	
	int arg_count = 1;
	argp_parse (&argp, argc, argv, 0, 0, &arg_count);

	options.vault="/home/qb/test.chv";
	options.entry="github\n"; 

	FILE* vp = fopen(options.vault, "r");

	int count = 0;
	char buffer[512];
	bool ispass = false;
	while (fgets(buffer, sizeof(buffer), vp) != NULL)
	{
		if (count % 2 == 0)
		{
			if (ispass)
			{
				printf("%s", buffer);
				break;
			}
			if (strcmp(buffer, options.entry) == 0)
			{
				count++;
				ispass = true;
			}
		}
		count++;
	}
	return 0;
}
