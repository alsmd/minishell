#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	pwd(void)
{
	char	buffer[500];

	printf("%s\n", getcwd(buffer, 500));
	g_minishell.exit_code = 0;
}
