#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	debuger(void)
{
	while (g_minishell.node)
	{
		if (g_minishell.node->argv[0])
			printf("nome: %s\n", g_minishell.node->argv[0]);
		else
			printf("sem nome\n");
		if (g_minishell.node->relation)
			printf("relation: %s\n", g_minishell.node->relation);
		else
			printf("sem relation\n");
		if (g_minishell.node->subshell)
			printf("é subshell: yes\n");
		else
			printf("é subshell: no\n");
		printf("--------\n");
		g_minishell.node = g_minishell.node->next;
	}
	exit(0);
}
