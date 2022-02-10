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
	else
		free(new_buffer);
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

char	*get_current_dir(void)
{
	char	*current_dir;
	char	buffer[500];
	char	*temp;
	char	*color;

	color = ft_strdup(g_minishell.color);
	current_dir = getcwd(buffer, 500);
	temp = ft_strjoin(color, cut_dir(current_dir));
	current_dir = ft_strjoin(temp, " > \033[0m");
	return(current_dir);
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
