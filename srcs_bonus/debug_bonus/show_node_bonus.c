#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	show_subshell(char *buffer)
{
	int		id;

	(void)id;
	id = fork();
	if (id == 0)
		debug_mode(buffer);
	waitpid(id, NULL, 0);
	free(buffer);
}

static void	print_argv(char **matrix, int size)
{
	int	i;
	int	c;

	i = 0;
	if (matrix[i] && matrix[i][0])
	{
		divider('-', size);
		while (matrix[i])
		{
			c = printf("|  %sArgs[%d]: %s%s%s", BOLD, i, CYAN, \
			matrix[i], RESET);
			indent(c, size);
			i++;
		}
	}
}

void	show_nodes(t_node *node)
{
	int	c;
	int	size;

	size = get_square_size(node);
	init_box(size);
	if (node->full_path && node->full_path[0])
		c = printf("|  %sName: %s%s%s", BOLD, CYAN, node->full_path, RESET);
	else
		c = printf("|  %sName: %sNone%s", BOLD, CYAN, RESET);
	indent(c, size);
	divider('-', size);
	if (node->relation)
		c = printf("|  %sRelation: %s%s%s", BOLD, CYAN, node->relation, RESET);
	else
		c = printf("|  %sRelation: %sNone%s", BOLD, CYAN, RESET);
	indent(c, size);
	if (node->subshell)
	{
		divider('-', size);
		c = printf("|  %sSubshell: %s%s", BOLD, CYAN, RESET);
		indent(c, size);
		c = printf("|%s%s     %s%s", BOLD, CYAN, node->subshell, RESET);
		indent(c, size);
	}
	print_argv(node->argv, size);
	divider('_', size);
}
