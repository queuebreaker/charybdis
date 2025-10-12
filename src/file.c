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

char*
ch_read(FILE* vp, char* entry)
{
	int i = 0;
	int line;
	char buffer[257];
	char* pass = malloc(sizeof(char) * 257);
	bool ispass = false;
	while (fgets(buffer, sizeof(buffer), vp) != NULL)
	{
		buffer[strcspn(buffer, "\n")] = 0;
		if (i % 2 == 0)
		{
			if (ispass)
			{
				strcpy(pass, buffer);
				break;
			}
			if (strcmp(buffer, entry) == 0)
			{
				i++;
				line = i;
				ispass = true;
			}
		}
		i++;
	}
	if (!ispass)
		pass = NULL;
	return pass;
}