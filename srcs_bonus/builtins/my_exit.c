#include <minishell.h>

extern t_minishell	g_minishell;

void	my_exit(char **argv)
{
	int	status;

	printf("exit\n");
	if (argv != 0)
	{
		if (argv[1] && argv[2])
		{
			show_error("exit: ", "too many arguments", 1, 0);
			g_minishell.exit_code = 1;
			return ;
		}
		if (argv[1])
		{
			status = ft_atoi(argv[1]);
			clean_trash();
			exit(status);
		}
	}
	clean_trash();
	exit(g_minishell.exit_code);
}
