/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:51:44 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	init_shell(char **envp)
{
	if (g_minishell.debug_mode == 0)
		init_term();
	init_minishell();
	g_minishell.matrix_env = envp;
	create_env(envp);
}

void	init_term(void)
{
	hazzard();
}

void	init_minishell(void)
{
	ft_bzero(&g_minishell, sizeof(t_minishell));
	g_minishell.color = ft_strdup(RED);
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
