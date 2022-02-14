#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	expand_node(t_node *node)
{
	int	index;

	index = 0;
	while (node->argv[index])
	{
		node->argv[index] = expand_vars(node->argv[index]);
		if (!expand_asterisk(node->argv[index], node, &index))
			index++;
	}
}

t_node	*get_next_chain(t_node *node)
{
	if ((node && node->relation && !ft_strncmp(node->relation, "&&", 2) \
	&& g_minishell.exit_code != 0) || (node && node->relation && \
	!ft_strncmp(node->relation, "||", 2) && g_minishell.exit_code == 0))
	{
		node = node->next;
		while (node && (!node->relation || (ft_strncmp
					(node->relation, "||", 2)
					&& ft_strncmp(node->relation, "&&", 2))))
			node = node->next;
		if (!node)
			return (node);
		if (!ft_strncmp(node->relation, "&&", 2)
			|| !ft_strncmp(node->relation, "||", 2))
			return (get_next_chain(node));
		return (node);
	}
	return (node);
}

void	execute_subshell(t_node *node)
{
	char	*buffer;

	buffer = ft_strdup(node->subshell);
	dup2(node->input, STDIN_FILENO);
	dup2(node->output, STDOUT_FILENO);
	clean_node();
	make_shell_command(buffer);
	clean_trash();
	exit(g_minishell.exit_code);
}

int	show_debug(t_node *node)
{
	if (g_minishell.debug_is_on && g_minishell.debug_mode == 1)
	{
		while (node)
		{
			expand_node(node);
			trim_quotes(node->argv);
			print_debuger_table(node);
			node = node->next;
		}
		return (1);
	}
	return (0);
}

void	exec_commands(t_node *node)
{
	int			status;

	status = 0;
	if (!node)
		node = g_minishell.node;
	if (show_debug(node))
		return ;
	while (node)
	{
		close_prev_fd(node);
		chose_execute_line(node, &status, 0);
		if (!node->relation || ((!ft_strncmp(node->relation, "||", 2)
					|| !ft_strncmp(node->relation, "&&", 2))))
			g_minishell.exit_code = status;
		if (g_minishell.debug_mode == 0)
			node = get_next_chain(node);
		if (node)
			node = node->next;
	}
	clean_trash();
	exit(g_minishell.exit_code);
}
