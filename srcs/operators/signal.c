#include <minishell.h>

extern	t_minishell g_minishell;



void handle_signal_child(int sig)
{
	(void)sig;
	write(1, "\n", 10);
	if (sig == SIGQUIT)
		exit(0);
}

void	handle_signal_parent(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(1, "\n", 1);
		// exit(0);
	}
}

void	signals(int sig)
{
	if (sig == PARENT)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_signal_parent);
	}	
	if (sig == CHILD)
	{
		signal(SIGINT, handle_signal_child);
		signal(SIGQUIT, handle_signal_child);
	}
	else if (sig == 3)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, handle_signal_parent);
	}
}