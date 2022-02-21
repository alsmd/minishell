/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:46:28 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell	g_minishell;

void	handle_signal_child(int sig)
{
	(void)sig;
	g_minishell.exit_code = 130;
	g_minishell.has_signal = 1;
}

void	handle_signal_parent(int sig)
{
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
