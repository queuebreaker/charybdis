#include "include.h"
#include "opts.h"

Entry_data
ch_find(FILE* vp, char* entry);

char*
ch_read(FILE* vp, int size);

int
ch_write(FILE* vp, char* entry, char* pass);

int
ch_delete(FILE* vp, int size, char* vault);