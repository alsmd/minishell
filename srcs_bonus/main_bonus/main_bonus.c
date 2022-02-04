#include <minishell_bonus.h>

t_minishell	g_minishell;

void	run(char *buffer)
{
	int		status;

	add_history(buffer);
	status = parse_string(buffer);
	if (status == 0)
		make_shell_command(buffer);
	else
		free(buffer);
	rl_replace_line("", 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*buffer;

	(void)argv;
	if (argc > 1)
	{
		printf("Invalid number of argument!\n");
		return (-1);
	}
	init_shell(envp);
	while (1)
	{
		signals(PARENT);
		buffer = readline("MiniShell Bonus > ");
		if (!buffer)
			my_exit(NULL);
		if (buffer[0] == '\0')
			continue ;
		run(buffer);
		clean_node();
	}
	return (0);
}
