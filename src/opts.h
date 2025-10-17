#include "random.h"

#ifndef OPTS_H
#define OPTS_H

int
parse_opts(int key, char* arg, struct argp_state* state);

extern struct argp_option
opts[];

extern struct argp
argp;

#endif