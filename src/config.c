#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>

struct options
{

};

char*
find_config(void)
{
	char* path = NULL;
	char* config_home;
	FILE* fd;

	if ((config_home = getenv("XDG_CONFIG_HOME")) == NULL) return NULL;
	sprintf(path, "%s/.config/chrc", config_home);
	if ((fd = fopen("config_path", "r")) == NULL) return NULL;

	return path;
}

