#include <minishell.h>

void	my_exit(char **argv)
{
	printf("exit\n");
	if (argv[1] && argv[2])
		show_error("exit: ", "too many arguments", 1, 0);
	if (argv[1])
		exit(ft_atoi(argv[1]));
	exit(0);
}
