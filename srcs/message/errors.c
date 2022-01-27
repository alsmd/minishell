#include <minishell.h>

extern t_minishell g_minishell;

void	show_error(char *name, char *message, int status, int has_to_exit)
{
	printf("Minishell: %s %s\n", name, message);
	g_minishell.node = 0;
	if (has_to_exit)
		exit(status);
}