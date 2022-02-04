#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	init_shell(char **envp)
{
	init_term();
	init_minishell();
	create_env(envp);
}

void	init_term(void)
{
	hazzard();
}

void	init_minishell(void)
{
	ft_bzero(&g_minishell, sizeof(t_minishell));
	g_minishell.operators = (char **) ft_calloc(9, sizeof(char *));
	g_minishell.operators[0] = ft_strdup("||");
	g_minishell.operators[1] = ft_strdup("<<");
	g_minishell.operators[2] = ft_strdup(">>");
	g_minishell.operators[3] = ft_strdup("<");
	g_minishell.operators[4] = ft_strdup(">");
	g_minishell.operators[5] = ft_strdup("|");
	g_minishell.operators[6] = ft_strdup("&&");
	g_minishell.operators[7] = NULL;
	g_minishell.operators[8] = ft_strdup(" ");
}
