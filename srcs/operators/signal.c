#include <minishell.h>

extern	t_minishell g_minishell;



void handle_signal_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	handle_signal_parent(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signals(int sig)
{
	if (sig == PARENT)
		signal(SIGINT, handle_signal_parent);
	if (sig == CHILD)
	{
		signal(SIGINT, handle_signal_child);
	}
	else if (sig == 3)
	{
		signal(SIGINT, SIG_IGN);
	}
}