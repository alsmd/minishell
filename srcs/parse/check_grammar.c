#include <minishell.h>

extern t_minishell	g_minishell;

int	check_grammar(void)
{
	t_node	*init;

	init = g_minishell.node;
	while (init->next)
	{
		if (init->relation && !init->next->argv[0])
		{
			printf("erro de sintax\n");
			return (1);
		}
		init = init->next;
	}
	return (0);
}
