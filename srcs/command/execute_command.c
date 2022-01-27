#include <minishell.h>

extern t_minishell g_minishell;

static void	create_relations(char *buffer)
{
	char		*relation;
	int			index;
	int first;

	index = 0;
	first = TRUE;
	while (buffer[index])
	{
		relation = is_in(g_minishell.operators, &(buffer[index]));
		if (relation)//<< EOF cat
		{	
			if (relation[0] == ' ')
			{
				g_minishell.operators[7] = NULL;
			}
			if (!ft_strncmp(&buffer[index], ">>", 2) || !ft_strncmp(&buffer[index], "<<", 2))
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

	fds = g_minishell.fds;
	while (fds)
	{
		if (fds->value != node->input && fds->value != node->output)
			close(fds->value);
		fds = fds->next;
	}
	dup2(node->input, STDIN_FILENO);
	dup2(node->output, STDOUT_FILENO);
	if (is_builtin(node))
		exec_builtin(node);
	else
	{
		if (node->not_exist == 1 && node->is_absolute_path)
			show_error(node->argv[0], M_INVALID_FILE, E_COMMAND_NOT_FOUND, 1);
		if (node->not_exist == 1)
			show_error(node->argv[0], M_COMMAND_NOT_FOUND, E_COMMAND_NOT_FOUND, 1);
		execve(node->argv[0], node->argv, get_matrix());
	}
	exit(0);
}


static void	link_relations(void)
{
	t_node		*node;

	node = g_minishell.node;
	while (node)//ls | wc
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
	int			status;

	node = g_minishell.node;
	status = 0;
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
			waitpid(id, &status, 0);
			//variavel global com o retorno do ctrl+c
			if (status == 2)
				printf("\n");
		}
		node = node->next;
	}
	exit(0);
}

void	make_shell_command(char *buffer)
{
	int			id;
	int			status;

	get_path();
	create_relations(buffer);
	if (check_grammar())
	{
		g_minishell.node = 0;
		return ;
	}
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
		waitpid(id, &status, 0);
	}
	g_minishell.node = 0;
}

