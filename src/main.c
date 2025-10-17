// ch - a password generation and management system



#include "include.h"
#include "opts.h"
#include "file.h"

Options options;

int
main(int argc, char** argv)
{
	int arg_count = 2;
	argp_parse (&argp, argc, argv, 0, 0, &arg_count);

	if (options.mode < 2)
	{
		switch (options.mode)
		{
			case ERROR:
			{
				error(1, 0, "invalid mode");
				break;
			}
			case VERSION:
			{
				printf("%s\n", CH_VERSION);
				return 0;
			}
			default:
				break;
		}
	}
	else
	{
		FILE* vp;
		if ((vp = fopen(options.vault, "a+b")) == NULL)
		{
			error(CH_EPATH, 0, "could not open vault: %s", options.vault);
		}

		Entry_data entry_data = ch_find(vp, options.entry);

		switch(options.mode)
		{
			case WRITE:
			{
				if (entry_data.offset != -1)
				{
					error(CH_EENTRY, 0, "entry exists: %s", options.entry);
				}

				if (options.pass == NULL)
				{
					options.pass = random_string(options.length, options.set);
				}

				ch_write(vp, options.entry, options.pass);

				break;
			}
			default:
			{
				if (entry_data.offset == -1)
				{
					error(CH_EENTRY, 0, "couldn't find entry: %s", options.entry);
				}

				fseek(vp, entry_data.offset, SEEK_SET);

				switch(options.mode)
				{
					case READ:
					{
						char* pass = ch_read(vp, entry_data.size);

						if (options.echo)
						{
							printf("%s", pass);
						}

						if (options.copy)
						{
							// TODO: copy
						}
						break;
					}
					case DELETE:
					{
						ch_delete(vp, entry_data.size, options.vault);
						break;
					}
					default:
						break;
				}
			}
		}
		fclose(vp);
	}
	return 0;
}