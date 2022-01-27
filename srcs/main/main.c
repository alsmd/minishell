#include <minishell.h>

t_minishell	g_minishell;

int	main(int argc, char *argv[], char *envp[])
{
	int		status;
	char	*buffer;
	char	*new_buffer;

	(void)argv;
	if (argc > 1)
	{
		printf("Invalid number of argument!\n");
		return (-1);
	}
	init_term();
	init_minishell();
	create_env(envp);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
			return (0);
		if (buffer[0] == '\0')
			continue ;
		if (!ft_strncmp(buffer, "exit", 4))
			return (0);
		add_history(buffer);
		new_buffer = expand_vars(buffer);
		status = parse_string(new_buffer);
		if (status == 0)
			make_shell_command(new_buffer);
	}
	return (0);
}
