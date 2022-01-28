#include <minishell.h>

void	my_exit(char **argv)
{
	int status;

	printf("exit\n");
	if (argv[1] && argv[2])
		show_error("exit: ", "too many arguments", 1, 0);
	if (argv[1])
	{
		status = ft_atoi(argv[1]);
		clean_trash();
		exit(status);
	}
	clean_trash();
	exit(0);
}
