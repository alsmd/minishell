#include <minishell.h>

extern	t_minishell g_minishell;

void	handle_signal(int sig)
{
	if (sig == SIGINT && g_minishell.execute_signal == TRUE)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}