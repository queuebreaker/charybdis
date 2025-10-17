#ifndef CONFIG_H
#define CONFIG_H

#include "include.h"

char*
ch_find_config(void);

Options
ch_parse_config(char* path);

#endif
