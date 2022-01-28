#include <minishell.h>

extern t_minishell	g_minishell;

void	show_error(char *name, char *message, int status, int has_to_exit)
{
	write(2, "Minishell: ", 12);
	write(2, name, ft_strlen(name));
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	g_minishell.node = 0;
	g_minishell.exit_code = status;
	if (has_to_exit)
	{
		clean_trash();
		exit(g_minishell.exit_code);
	}
}
