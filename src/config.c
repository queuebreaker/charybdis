#include "include.h"

// TODO
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

