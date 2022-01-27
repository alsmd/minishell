#include <minishell.h>

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n> ");
		rl_replace_line("", 0);
	}
}