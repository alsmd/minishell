#include <minishell.h>

t_minishell	g_minishell;

void	run(char *buffer)
{
	char	*new_buffer;
	int		status;

	add_history(buffer);
	new_buffer = expand_vars(buffer);
	status = parse_string(new_buffer);
	if (status == 0)
		make_shell_command(new_buffer);
	rl_replace_line("", 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buffer;

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
		buffer = readline("MiniShell > ");
		if (!buffer)
		{
			write(1, "\n", 1);
			return (0);
		}
		if (buffer[0] == '\0')
			continue ;
		run(buffer);
	}
	return (0);
}
