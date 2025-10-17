#include "include.h"

extern Options options;

int
argp_parse_opts(int key, char* arg, struct argp_state* state)
{
	int *arg_count = state->input;
	switch(key)
	{
		case ARGP_KEY_ARG:
		{
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
					options.mode = ERROR;
				}
			}
			else
			{
				options.entry = arg;
			}
			break;
		}
		case ARGP_KEY_END:
		{
			if (*arg_count >= 1)
			{
				error(CH_EARGC, 0, "too few arguments");
			}
			else if (*arg_count < 0)
			{
				error(CH_EARGC, 0, "too many arguments");
			}
			break;
		}
		case 'v':
			options.vault = arg;
			break;
		case 'C':
			options.vault = arg;
			break;
		case 'p':
			options.pass = arg;
			break;
		case 'l':
			options.length = atoi(arg);
			break;
		case 's':
			options.set = arg;
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
	{"pass", 'p', "PASS", 0, "Write specified password directly", 1},
	{"length", 'l', "LEN", 0, "(write mode only) Generate password with specified length. Default value is 8", 2},
	{"set", 's', "SET", 0, "(write mode only) Generate password using symbols part of specified set", 2},
	{"verbose", 1001, NULL, 0, "Explain what is being done", 2},
	{"copy", 'c', NULL, 0, "(wayland only) Copy password to clipboard", 3},
	{"echo", 'e', NULL, 0, "Echo password to stdin", 3},
	{"version", 1002, NULL, 0, "Print program version", 4}

};

struct argp
argp = {argp_opts, argp_parse_opts, "[MODE] [ENTRY]", 0, 0, 0, 0};