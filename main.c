#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int echo(int argc, char* argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		printf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');
	}
	return argc - 1;
}

int retcode(int ret_code)
{
	printf("%d\n", ret_code);
	return 0;
}

int main(int argc, char* argv[])
{
	int ret_code = 0;

	char str[512];
	char* res_str = NULL;
	char* w_str = NULL;

	while (fgets(str, sizeof str, stdin))
	{
		char* sub_str = strtok_r(str, "\n;", &res_str);
		while (sub_str != NULL)
		{
			argc = 0;

			char* w_mark = strtok_r(sub_str, " ", &w_str);
			while (w_mark != NULL)
			{
				argv[argc++] = w_mark;
				w_mark = strtok_r(NULL, " ", &w_str);
			}

			if (!strcmp(argv[0], "retcode"))
				retcode(ret_code);
			else
				if (!strcmp(argv[0], "echo"))
					ret_code = echo(argc, argv);
				else
					printf("%s", "\nUnknown command\n");

			sub_str = strtok_r(NULL, "\n;", &res_str);
		}
	}
	return 0;
}