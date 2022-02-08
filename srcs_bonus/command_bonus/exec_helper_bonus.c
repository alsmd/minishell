#include <minishell_bonus.h>

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
	printf("%s\033[1;97m\"%s\" \033[33m☣\033[0m\n", M_UNK, argv[0]);
	free_matrix(argv);
	free_matrix(env);
	free(path);
	exit(get_status(g_minishell.exit_code));
}

static void	execute_cmd(t_node *node)
{
	t_fd	*fds;

	expand_node(node);
	trim_quotes(g_minishell.node->argv);
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

void	execute_subshell(t_node *node)
{
	char	*buffer;

	buffer = ft_strdup(node->subshell);
	clean_node();
	make_shell_command(buffer);
	clean_trash();
	exit(g_minishell.exit_code);
}

void	close_prev_fd(t_node *node)
{
	if (node->previous && is_command(node->previous))
	{
		close_fd(node->previous->input);
		close_fd(node->previous->output);
	}
}

void	validade_command(t_node *node)
{
	if (node->not_exist == 1 && node->is_absolute_path)
		show_error(node->argv[0], M_INVALID_FILE, E_COMMAND_NOT_FOUND, 1);
	else if (node->is_absolute_path && \
	node->is_executable == 0 && node->not_exist == 0)
		show_error(node->argv[0], M_PERMISSION, E_PERMISSION, 1);
	else if (node->not_exist == 1)
		show_error(node->argv[0], M_COMMAND_NOT_FOUND, \
		E_COMMAND_NOT_FOUND, 1);
	else if (node->invalid_file)
		show_error(node->invalid_file, M_INVALID_FILE, E_COMMAND_NOT_FOUND, 1);
}
