#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	show_subshell(char *buffer)
{
	int	id;

	(void)id;
	printf("|%s|\n", buffer);
	id = fork();
	if (id == 0)
	{
		g_minishell.debug_mode = 1;
		make_shell_command(buffer);
		exit(0);
	}
	waitpid(id, NULL, 0);
}

void	show_nodes(t_node *node)
{
	int	i;

	i = 0;
	if (node->argv[0])
		printf("nome: %s\n", node->argv[0]);
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
