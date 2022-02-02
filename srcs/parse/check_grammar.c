#include <minishell.h>

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
				show_error(M_ERROR_SINTAX, init->relation, 2, 0);
			else
				show_error(M_ERROR_SINTAX, "'newline'", 2, 0);
			return (1);
		}
		if (init->relation && (!ft_strncmp(init->relation, ">", -1) || \
		!ft_strncmp(init->relation, ">>", -1)) && init->next && \
		init->next->argv && !ft_strncmp(init->next->argv[0], "/", -1))
		{
			printf("%s\033[33m☣\033[0m\n", M_UNK);
			return (1);
		}
		init = init->next;
	}
	return (0);
}
