#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	handle_signal_child(int sig)
{
	(void)sig;
	g_minishell.exit_code = 130;
	g_minishell.has_signal = 1;
}

void	handle_signal_parent(int sig)
{
	//write(1, "parent\n", 8);
	(void)sig;
	g_minishell.exit_code = 130;
	g_minishell.has_signal = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	g_minishell.exit_code = 131;
	g_minishell.has_signal = 1;
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
		signal(SIGQUIT, handle_sigquit);
	}
	if (sig == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
