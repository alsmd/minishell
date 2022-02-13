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

void	show_nodes(t_node *node)
{
	int	i;

	i = 0;
	if (node->full_path)
		printf("nome: %s\n", node->full_path);
	else
		printf("sem nome\n");
	if (node->relation)
		printf("relation: %s\n", node->relation);
	else
		printf("sem relation\n");
	if (node->argv)
	{
		while (node->argv[i])
		{
			printf("args: %s\tindex: %d\n", node->argv[i], i);
			i++;
		}
	}
	printf("--------\n");
}
