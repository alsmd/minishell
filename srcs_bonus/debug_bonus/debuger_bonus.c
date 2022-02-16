/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuger_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:51:19 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:51:20 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	debug_mode(char *buffer)
{
	t_debug	debug_flags;
	int		tab;

	tab = g_minishell.tab_indentation;
	debug_flags = g_minishell.debug_flags;
	g_minishell.debug_mode = 1;
	clean_trash();
	init_shell(g_minishell.matrix_env);
	g_minishell.debug_mode = 1;
	g_minishell.tab_indentation = tab;
	g_minishell.debug_is_on = 1;
	g_minishell.debug_flags = debug_flags;
	make_shell_command(buffer);
	clean_trash();
	exit(0);
}

void	print_debuger_table(t_node *node)
{
	if (g_minishell.debug_flags.show_nodes)
		show_nodes(node);
	if (g_minishell.debug_flags.show_subshell && node->subshell)
		show_subshell(ft_strdup(node->subshell));
}

void	debuger(char **flags)
{
	if (!g_minishell.debug_is_on)
	{
		printf("Debug mode is enable!\n");
		g_minishell.debug_is_on = 1;
	}
	else if (flags && !flags[1])
	{
		printf("Debug mode is disable!\n");
		ft_bzero(&g_minishell.debug_flags, sizeof(t_debug));
		g_minishell.debug_mode = 0;
		g_minishell.debug_is_on = 0;
	}
	if (g_minishell.debug_is_on && flags[1])
		turn_on_debug_flags(flags);
}
