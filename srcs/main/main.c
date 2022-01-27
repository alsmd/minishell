#include <minishell.h>

t_minishell	g_minishell;

void	*set_string(char *src, char *dest)
{
	while (*dest)
	{
		*src = *dest;
		src++;
		dest++;
	}
}

// || | && < > << >> 
void	init_minishell(void)
{
	ft_bzero(&g_minishell, sizeof(t_minishell));
	g_minishell.operators = (char **) ft_calloc(9, sizeof(char *));
	g_minishell.operators[0] = ft_strdup("|");
	g_minishell.operators[1] = ft_strdup("<<");
	g_minishell.operators[2] = ft_strdup(">>");
	g_minishell.operators[3] = ft_strdup("<");
	g_minishell.operators[4] = ft_strdup(">");
	g_minishell.operators[5] = ft_strdup("||");
	g_minishell.operators[6] = ft_strdup("&&");
	g_minishell.operators[7] = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	int		status;
	char	*buffer;
	char	*new_buffer;

	init_minishell();
	create_env(envp);
	while (1)
	{
		buffer = readline("> ");
		if (buffer[0] == 0)
			continue ;
		if (!ft_strncmp(buffer, "exit", 4))
			return (0);
		add_history(buffer);
		new_buffer = expand_vars(buffer);
		status = parse_string(new_buffer);
		if (status != 0)
			printf("Error Sintaxe\n");
		if (status == 0)
			make_shell_command(new_buffer);
	}
	return (0);
}
