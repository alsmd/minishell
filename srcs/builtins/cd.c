#include <minishell.h>

void cd(char **argv)
{
	if (argv[2] != 0)
		show_error("cd: ", "too many arguments", 1, 0);
	chdir(argv[1]);
}