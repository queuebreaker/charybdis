#include "include.h"
#include "opts.h"

Entry_data
ch_find(FILE *vp, const char *entry)
{
	Entry_data data = { .offset = -1, .size = 0 };
	bool found = false;
	long start = 0;
	long offset = 0;
	char buffer[257];

	rewind(vp);

	while (fgets(buffer, sizeof buffer, vp) != NULL)
	{
		buffer[strcspn(buffer, "\n")] = '\0';

		if (!found && strcmp(buffer, entry) == 0)
		{
			found = true;
			start = offset;
		}
		else
		{
			data.offset = start;
			data.size = (offset + strlen(buffer) + 1) - start;
			break;
		}
		offset += strlen(buffer) + 1;
	}
	return data;
}

// Entry_data
// ch_find(FILE *vp, const char *entry)
// {
// 	Entry_data data = { .offset = -1, .size = 0 };
// 	int i = 0;
// 	long offset = 0;
// 	long start = 0;
// 	int line = 0;
// 	bool found = false;

// 	rewind(vp);

// 	char buffer[257];
// 	while (fgets(buffer, sizeof(buffer), vp) != NULL)
// 	{
// 		buffer[strcspn(buffer, "\n")] = '\0';
// 		printf("%d\t%s\n", i, buffer);
// 		if(i % 2 == 0)
// 		{
// 			if (!found && strcmp(buffer, entry) == 0) {
// 				found = true;
// 				start = offset;
// 			}
// 		if (found)
// 			{
// 				++line;
// 				if (line == 2)
// 				{
// 				data.offset = start;
// 				data.size  = offset - start;
// 				break;
// 				}
// 			}
// 		}
// 		offset += strlen(buffer) + 1;
// 		i++;
// 	}
// 	return data;
// }

char*
ch_read(FILE* vp, int size)
{
	char buffer[257]  = { 0 };

	size_t fread_size;
	if ((size_t)size < sizeof(buffer) - 1)
	{
		fread_size = (size_t)size;
	}
	else
	{
		fread_size = sizeof(buffer);
	}

	fread(buffer, 1, fread_size, vp);
	buffer[fread_size] = '\0';

	char* pass = strchr(buffer, '\n');
	if (pass)
	{
		*pass = '\0';
		++pass;
	}

	char* out = malloc(strlen(pass) + 1);
	strcpy(out, pass);

	return out;
}

int
ch_write(FILE* vp, char* entry, char* pass)
{
	if (fprintf(vp, "%s\n%s\n", entry, pass) < 0)
	{
		return 1;
	}
	return 0;
}

int
ch_delete(FILE* vp, int size, char* vault)
{
	char tmp_path[4096];
	char bk_path[4096];
	snprintf(tmp_path, sizeof(tmp_path), "%s.tmp", vault);
	snprintf(bk_path, sizeof(bk_path), "%s.bk", vault);

	FILE* tmp = fopen(tmp_path, "wb");
	if (!tmp)
	{
		return -1;
	}

	char buffer[257];
	long start = ftell(vp);

	rewind(vp);

	while (ftell(vp) < start)
	{
		fgets(buffer, sizeof(buffer), vp);
		fputs(buffer, tmp);
	}

	fseek(vp, start + size, SEEK_SET);

	while (fgets(buffer, sizeof(buffer), vp))
	{
		fputs(buffer, tmp);
	}

	fflush(tmp);
	fclose(tmp);

	rename(vault, bk_path);
	rename(tmp_path, vault);
	unlink(bk_path);

	return 0;
}