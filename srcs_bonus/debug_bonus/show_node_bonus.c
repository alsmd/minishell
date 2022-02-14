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

static void	print_argv(char **matrix)
{
	int	i;

	i = 0;
	if (matrix[i] && matrix[i][0])
	{
		printf("----------------------\n|");
		while (matrix[i])
		{
			printf("  %sArgs[%d]: %s%s\n%s|", BOLD, i, CYAN, \
			matrix[i], RESET);
			i++;
		}
	}
}

void	show_nodes(t_node *node)
{
	printf(" ______________________\n|\n|");
	if (node->full_path && node->full_path[0])
		printf("  %sName: %s%s\n%s|", BOLD, CYAN, node->full_path, RESET);
	else
		printf("  %sName: %sNone\n%s|", BOLD, CYAN, RESET);
	printf("----------------------\n|");
	if (node->relation)
		printf("  %sRelation: %s%s\n%s|", BOLD, CYAN, node->relation, RESET);
	else
		printf("  %sRelation: %sNone%s\n|", BOLD, CYAN, RESET);
	if (node->subshell)
	{
		printf("----------------------\n|");
		printf("  %sSubshell: %s\n|%s     %s\n%s|", BOLD, RESET, CYAN, \
		node->subshell, RESET);
	}
	print_argv(node->argv);
	printf("______________________\n");
}
