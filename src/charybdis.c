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

	if (options.mode < 2)
	{
		printf("testing");
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
		if ((vp = fopen(options.vault, "a+")) == NULL)
			error(CH_EPATH, 0, "could not open path: %s", options.vault);
		if (options.mode == WRITE && options.pass == NULL)
			options.pass = random_string(options.length, options.set);
		ch_file(vp, options);

		fclose(vp);
	}
	return 0;
}
