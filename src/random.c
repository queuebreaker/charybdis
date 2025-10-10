#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#include "random.h"

char* random_string (int length, char* set)
{
	char* string = NULL;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	srand((long)tv.tv_usec);
	if (length)
	{
		string = malloc(sizeof(char) * (length + 1));
		if (string)
		{
			for (int i = 0l; i < length; i++)
			{
				int r = rand() % (int)(strlen(set) - 1);
				string[i] = set[r];
			}
			string[length] = '\0';
			return string;
		}
	}
	return NULL;
}



