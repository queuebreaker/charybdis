// ch - a password generation and management system

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <argp.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>

#include "include.h"
#include "opts.h"
#include "file.h"

Options options;

int
main(int argc, char** argv)
{
	int arg_count = 2;
	argp_parse (&argp, argc, argv, 0, 0, &arg_count);

	if (options.mode < 3)
	{
		switch (options.mode)
		{
			case ERROR:
				error(1, 0, "invalid mode");
				break;
			case VERSION:
				printf("%s\n", CH_VERSION);
				return 0;
			default:
				// unreachable
				break;
		}
	}
	else
	{
		FILE* vp;
		if ((vp = fopen(options.vault, "r+")) == NULL)
		{
			error(CH_EPATH, 0, "could not open path: %s", options.vault);
		}
		switch (options.mode)
		{
			case WRITE:
			{
				// if (ch_write(options.vault, options.entry, options.pass) != 0)
				// 	error(1, 0, "couldn't write");
				break;
			}
			case READ:
			{
				char* pass;
				if ((pass = ch_read(vp, options.entry)) == NULL)
				{
					error(1, 0, "%s: couldnt find entry", options.entry);
				}
				if (options.echo == true)
				{
					printf("%s\n", pass);
				}
				// TODO: copy
				break;
			}
			case DELETE:
			{
				// if (ch_read(options.vault, options.entry, options.pass) != 0)
				// 	error(1, 0, "couldn't delete");
				break;
			}
			default:
				// unreachable
				break;
		}
		fclose(vp);
	}
	return 0;
}
