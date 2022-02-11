#include <minishell_bonus.h>

t_minishell	g_minishell;

void	run(char *buffer)
{
	int		status;
	int		id;

	add_history(buffer);
	status = parse_string(buffer);
	if (status == 0)
	{
		if (g_minishell.debug_is_on)
		{
			g_minishell.debug_mode = 1;
			id = fork();
			if (id == 0)
			{
				make_shell_command(buffer);
				exit(0);
			}
			waitpid(id, NULL, 0);
			g_minishell.debug_mode = 0;
		}
		if ((!ft_strncmp(buffer, "debug ", 5)) && g_minishell.debug_is_on)
			make_shell_command(buffer);
		else if (!g_minishell.debug_is_on || g_minishell.debug_flags.exec_cmd)
			make_shell_command(buffer);
	}
	else
		free(buffer);
	rl_replace_line("", 0);
}

char	*cut_dir(char *buffer)
{
	int	i;

	i = ft_strlen(buffer) - 1;
	while (i >= 0 && buffer[i] != '/')
		i--;
	if (buffer[i] == '/')
		i++;
	return (&buffer[i]);
}

char	*get_user(void)
{
	char	*user;
	char	*tmp;

	user = get_var_value("USER");
	if (*user == 0)
	{
		free(user);
		return (ft_strdup("[Unkown] "));
	}
	tmp = user;
	user = ft_strjoin(ft_strdup("["), user);
	free(tmp);
	user = ft_strjoin(user, "] ");
	return (user);
}

char	*get_current_dir(void)
{
	char	*current_dir;
	char	buffer[500];
	char	*temp;
	char	*color;
	char	*user;

	user = get_user();
	color = ft_strdup(g_minishell.color);
	current_dir = getcwd(buffer, 500);
	temp = ft_strjoin(ft_strdup(BLUE), user);
	temp = ft_strjoin(temp, color);
	temp = ft_strjoin(temp, cut_dir(current_dir));
	temp = ft_strjoin(temp, BLUE);
	current_dir = ft_strjoin(temp, "-$> \033[0m");
	free(color);
	free(user);
	return (current_dir);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*buffer;
	char	*locate;

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
		locate = get_current_dir();
		buffer = readline(locate);
		free(locate);
		if (!buffer)
			my_exit(NULL);
		if (buffer[0] == '\0')
			continue ;
		run(buffer);
		clean_node();
	}
	return (0);
}
