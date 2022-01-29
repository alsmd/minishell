#include <minishell.h>

extern t_minishell	g_minishell;

static void	exec_extern_cmd(t_node *node)
{
	char	**argv;
	char	**env;
	char	*path;

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
	if (node->is_builtin == 1)
		exec_builtin(node);
	else
	{
		validade_command(node);
		exec_extern_cmd(node);
	}
	clean_trash();
	exit(g_minishell.exit_code);
}

void	exec_commands(void)
{
	t_node		*node;
	int			id;

	node = g_minishell.node;
	while (node)
	{
		close_prev_fd(node);
		if (is_command(node))
		{
			id = fork();
			signals(3);
			if (id == 0)
			{
				signals(CHILD);
				execute_cmd(node);
			}
			waitpid(id, &g_minishell.exit_code, 0);
			g_minishell.exit_code = get_status(g_minishell.exit_code);
		}
		node = node->next;
	}
	clean_trash();
	exit(g_minishell.exit_code);
}
			// if (g_minishell.exit_code == 2)
			// 	printf("\n");

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
}
