#include <minishell.h>

extern t_minishell	g_minishell;

void	init_minishell(void)
{
	ft_bzero(&g_minishell, sizeof(t_minishell));
	g_minishell.operators = (char **) ft_calloc(9, sizeof(char *));
	g_minishell.operators[0] = ft_strdup("|");
	g_minishell.operators[1] = ft_strdup("<<");
	g_minishell.operators[2] = ft_strdup(">>");
	g_minishell.operators[3] = ft_strdup("<");
	g_minishell.operators[4] = ft_strdup(">");
	g_minishell.operators[5] = ft_strdup("||");
	g_minishell.operators[6] = ft_strdup("&&");
	g_minishell.operators[7] = NULL;
	g_minishell.sa.sa_handler = &handle_signal;
	sigaction(SIGINT, &g_minishell.sa, NULL);
}