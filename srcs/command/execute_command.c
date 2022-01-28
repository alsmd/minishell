#include <minishell.h>

extern t_minishell	g_minishell;

int get_status(int status)
{
    return (((status) & 0xff00) >> 8);
}

char	*create_node(char *buffer, int first, int index, char *relation)
{
	if (relation[0] == ' ')
	{
		g_minishell.operators[7] = NULL;
	}
	if (!ft_strncmp(&buffer[index], ">>", 2) ||\
	!ft_strncmp(&buffer[index], "<<", 2))
	{
		buffer[index] = '\0';
		index++;
	}
	buffer[index] = '\0';
	index++;
	add_new_cmd(buffer, relation);
	buffer += index;
	if (first == TRUE && g_minishell.node->argv[0] == 0)
	{
		while (*buffer && *buffer == ' ')
			buffer++;
		g_minishell.operators[7] = " ";
		g_minishell.operators[8] = NULL;
	}
	return (buffer);
}

static void	create_relations(char *buffer)
{
	char	*relation;
	int		index;
	int		first;

	index = 0;
	first = TRUE;
	while (buffer[index])
	{
		relation = is_in(g_minishell.operators, &(buffer[index]));
		if (relation)
		{	
			buffer = create_node(buffer, first, index, relation);
			index = 0;
			first = FALSE;
		}
		else
			index++;
	}
	if (*buffer != 0)
		add_new_cmd(buffer, 0);
}

static void	execute_cmd(t_node *node)
{
	t_fd	*fds;
	char	**argv;
	char	**env;
	char 	*path;

	fds = g_minishell.fds;
	while (fds)
	{
		if (fds->value != node->input && fds->value != node->output)
			close(fds->value);
		fds = fds->next;
	}
	dup2(node->input, STDIN_FILENO);
	dup2(node->output, STDOUT_FILENO);
	// printf("%s\n", node->argv[0]);
	if (node->is_builtin == 1)
		exec_builtin(node);
	else
	{
		if (node->not_exist == 1 && node->is_absolute_path)
			show_error(node->argv[0], M_INVALID_FILE, E_COMMAND_NOT_FOUND, 1);
		else if(node->is_absolute_path && node->is_executable == 0 && node->not_exist == 0)
			show_error(node->argv[0], M_PERMISSION, 
			E_PERMISSION, 1);
		else if (node->not_exist == 1)
			show_error(node->argv[0], M_COMMAND_NOT_FOUND, \
			E_COMMAND_NOT_FOUND, 1);
		else
		{
			argv = node->argv;
			node->argv = 0;
			path = node->full_path;
			node->full_path = 0;
			env = get_matrix();
			clean_trash();
			g_minishell.exit_code = execve(path, argv, env);
			printf("\033[1;31mUnknown error!!!\033[33m☣\033[0m\n");
			free_matrix(argv);
			free_matrix(env);
			free(path);
			exit(get_status(g_minishell.exit_code));
		}
	}
	clean_trash();
	exit(g_minishell.exit_code);
}

static void	link_relations(void)
{
	t_node	*node;

	node = g_minishell.node;
	while (node)
	{
		if (node->relation == 0)
			break ;
		if (node->relation[0] == '|')
			handle_pipe(node);
		else if (node->relation[0] == '>')
			handle_output(node);
		else if (node->relation[0] == '<' \
		&& node->relation[1] == '\0')
			handle_input(node);
		else if (!ft_strncmp(node->relation, "<<", 2))
			handle_here_doc(node);
		node = node->next;
	}
}


static void	exec_commands(void)
{
	t_node		*node;
	int			id;

	node = g_minishell.node;
	while (node)
	{
		if (is_command(node))
		{
			if (node->previous)
			{
				close_fd(node->previous->input);
				close_fd(node->previous->output);
			}
			id = fork();
			signals(3);
			if (id == 0)
			{
				signals(CHILD);
				execute_cmd(node);
			}
			waitpid(id, &g_minishell.exit_code, 0);
			// if (g_minishell.exit_code == 2)
			// 	printf("\n");
			g_minishell.exit_code = get_status(g_minishell.exit_code);
		}
		node = node->next;
	}
	clean_trash();
	exit(g_minishell.exit_code);
}

void	make_shell_command(char *buffer)
{
	int			id;

	get_path();
	create_relations(buffer);
	free(buffer);
	if (check_grammar())
		return ;
	if (is_builtin(g_minishell.node) == TRUE && g_minishell.node->next == 0)
		exec_builtin(g_minishell.node);
	else
	{
		id = fork();
		signals(3);
		if (id == 0)
		{
			link_relations();
			exec_commands();
		}
		waitpid(id, &g_minishell.exit_code, 0);
		g_minishell.exit_code = get_status(g_minishell.exit_code);
	}
	
	// printf("\n|%d|\n", g_minishell.exit_code);
}
