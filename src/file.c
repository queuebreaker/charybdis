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

void
ch_file(FILE* vp, Options options)
{
	switch(options.mode)
	{
		case WRITE:
		{
			fprintf(vp, "\n%s\n%s", options.entry, options.pass);
			printf("success!\n");
			break;
		}
		case READ || DELETE:
		{
			// TODO: redo everything here, implement delete
			int i;
			i = 0;
			int line;
			char buffer[257];
			char* pass = malloc(sizeof(char) * 257);
			bool is_entry = false;
			while (fgets(buffer, sizeof(buffer), vp) != NULL)
			{
				buffer[strcspn(buffer, "\n")] = 0;
				if (i % 2 == 0)
				{
					if (is_entry)
					{
						if (options.mode == WRITE)
							strcpy(pass, buffer);
						else if (options.mode == DELETE)
							printf("not implemented, sorry\n");
						break;
					}
					if (strcmp(buffer, options.entry) == 0)
					{
						i++;
						line = i;
						is_entry = true;
					}
				}
				i++;
			}
			if (options.echo == true)
			{
				printf("%s\n", pass);
			}
		}
		default:
			// unreachable
			break;
	}
}