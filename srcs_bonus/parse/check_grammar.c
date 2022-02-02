#include <minishell_bonus.h>

extern t_minishell	g_minishell;

int	check_grammar(void)
{
	t_node	*init;

	init = g_minishell.node;
	while (init)
	{
		if (init->relation && (!init->next || \
		!init->next->argv || !init->next->argv[0]))
		{
			if (!ft_strncmp(init->relation, "|", 1))
				show_error(" syntax error near unexpected \
				token ", init->relation, 2, 0);
			else
				show_error(" syntax error near unexpected \
				token ", "'newline'", 2, 0);
			return (1);
		}
		init = init->next;
	}
	return (0);
}
