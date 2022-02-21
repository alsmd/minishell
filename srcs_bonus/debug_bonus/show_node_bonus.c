/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_node_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:51:29 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	show_subshell(char *buffer)
{
	int		id;

	g_minishell.tab_indentation += 2;
	id = fork();
	if (id == 0)
		debug_mode(buffer);
	waitpid(id, NULL, 0);
	free(buffer);
	g_minishell.tab_indentation = 0;
}

void	show_nodes(t_node *node)
{
	int	size;

	size = get_square_size(node);
	header_box(size);
	module_name(node, size);
	module_relation(node, size);
	module_subshell(node, size);
	module_argv(node->argv, size);
	footer_box(size);
}
