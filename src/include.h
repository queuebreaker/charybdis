#ifndef INC_H
#define INC_H

// custom error exit codes
#define CH_ERR 1 	// general-purpose
#define CH_EARGC 2	// argc error
#define CH_EMODE 3	// invalid mode
#define CH_EPATH 4	// invalid path
#define CH_EENTRY 5	// invalid entry
#define CH_EFILE 6	// file error

#define CH_VERSION "0.1"

typedef enum
{
	ERROR,
	VERSION,
	WRITE,
	READ,
	DELETE,
} Mode;

typedef struct
{
	Mode mode;
	bool echo;
	bool copy;
	bool verbose;
	char* entry;
	char* vault;
	char* config;
	char* set;
	int length;
	char* pass;
} Options;

typedef struct
{
	long offset;
	int size;
} Entry_data;

#endif