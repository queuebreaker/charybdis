// ch - a password generation and management system

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <argp.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>

#define CHE_GP 1
#define CHE_ARGC 2
#define CHE_MODE 3
#define CHE_PATH 4
#define CHE_VAL 5

#define CH_VERSION "0.1"

typedef enum
{
	WRITE,
	READ,
	DELETE,
	VERSION
} Mode;

typedef struct
{
	Mode mode;
	bool echo;
	bool copy;
	bool verbose;
	char* entry;
	char* vault;
	char* config;
	char* set;
	int length;
} Options;

Options options;

int
argp_parse_opts(int key, char* arg, struct argp_state* state)
{
	int *arg_count = state->input;
	switch(key)
	{
		case ARGP_KEY_ARG:
			(*arg_count)--;
			if (*arg_count == 1)
			{
				if (strcmp(arg, "write") == 0)
				{
					options.mode = WRITE;
				}
				else if (strcmp(arg, "read") == 0)
				{
					options.mode = READ;
				}
				else if (strcmp(arg, "delete") == 0)
				{
					options.mode = DELETE;
				}
				else
				{
					error(CHE_MODE , 0, "invalid mode: %s", arg);
				}
			}
			else
			{
				options.entry = arg;
			}
			break;
		case ARGP_KEY_END:
			if (*arg_count >= 1)
			{
				error(CHE_ARGC, 0, "too few arguments");
			}
			else if (*arg_count < 0)
			{
				error(CHE_ARGC, 0, "too many arguments");
			}
			break;
		case 'v':
			if (access(arg, R_OK & W_OK) != 0)
			{
				error(CHE_PATH, 0, "invalid vault path: %s", arg);
			}
			else
			{
				options.vault = arg;
			}
			break;
		case 'C':
			if (access(arg, R_OK & W_OK) != 0)
			{
				error(CHE_PATH, 0, "invalid config path: %s", arg);
			}
			else
			{
				options.vault = arg;
			}
			break;
		case 'l':
			if (atoi(arg) < 1 || atoi(arg) > 256)
			{
				error(CHE_VAL, 0, "invalid value: %s", arg);
			}
			else
			{
				options.length = atoi(arg);
			}
			break;
		case 's':
			if (strlen(arg) < 1 || strlen(arg) > 64)
			{
				error(CHE_VAL, 0, "invalid value: %s", arg);
			}
			else
			{
				options.set = arg;
			}
			break;
		case 1001:
			options.verbose = true;
			break;
		case 'c':
			options.copy = true;
			break;
		case 'e':
			options.echo = true;
			break;
		case 1002:
			options.mode = VERSION;
			break;
	}
return 0;
}

struct argp_option
argp_opts[] =
{
	{"vault", 'v', "PATH", 0, "Manipulate specified vault. Default value is '$HOME/.vault.chv'", 1},
	{"config", 'C', "PATH", 0, "Use specified config. Default value is '$XDG_CONFIG_HOME/chrc'", 1},
	{"length", 'l', "LEN", 0, "(write mode only) Generate password with specified length. Default value is 8", 2},
	{"set", 's', "SET", 0, "(write mode only) Generate password using symbols part of specified set", 2},
	{"verbose", 1001, NULL, 0, "Explain what is being done", 2},
	{"copy", 'c', NULL, 0, "(wayland only) Copy password to clipboard", 3},
	{"echo", 'e', NULL, 0, "Echo password to stdin", 3},
	{"version", 1002, NULL, 0, "Print program version", 4}

};

struct argp
argp = {argp_opts, argp_parse_opts, 0, 0, 0, 0, 0};

int
main(int argc, char** argv)
{
	int arg_count = 2;
	argp_parse (&argp, argc, argv, 0, 0, &arg_count);

	switch (options.mode)
	{
		case 0: // WRITE
			break;
		case 1: // READ
		{
			FILE* vp = fopen(options.vault, "r");

			if (vp == NULL)
			{
				error(CHE_PATH, 0, "invalid path: %s", options.vault);
			}

			int count = 0;
			char buffer[257];
			char pass[257];
			bool ispass = false;
			while (fgets(buffer, sizeof(buffer), vp) != NULL)
			{
				buffer[strcspn(buffer, "\n")] = 0;
				if (count % 2 == 0)
				{
					if (ispass)
					{
						strcpy(pass, buffer);
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
			if (!ispass)
			{
				error(1, 0, "could not find password: %s", options.entry);
			}
			if (options.echo)
			{
				printf("%s", pass);
			}

			break;
		}
		case 2: // DELETE
			break;
		case 3: // VERSION
			break;
	}
	return 0;
}
