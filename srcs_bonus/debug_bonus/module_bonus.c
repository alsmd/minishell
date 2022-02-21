/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   module_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:51:25 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	module_name(t_node *node, int size)
{
	int	c;

	print_char(' ', g_minishell.tab_indentation);
	if (node->full_path && node->full_path[0])
		c = printf("|  %sName: %s%s%s", BOLD, CYAN, node->full_path, RESET);
	else
		c = printf("|  %sName: %sNone%s", BOLD, CYAN, RESET);
	indent(c, size);
	print_char(' ', g_minishell.tab_indentation);
	divider('-', size);
}

void	module_relation(t_node *node, int size)
{
	int	c;

	print_char(' ', g_minishell.tab_indentation);
	if (node->relation)
		c = printf("|  %sRelation: %s%s%s", BOLD, CYAN, node->relation, RESET);
	else
		c = printf("|  %sRelation: %sNone%s", BOLD, CYAN, RESET);
	indent(c, size);
}

void	module_subshell(t_node *node, int size)
{
	int	c;

	if (node->subshell)
	{
		print_char(' ', g_minishell.tab_indentation);
		divider('-', size);
		print_char(' ', g_minishell.tab_indentation);
		c = printf("|  %sSubshell: %s%s", BOLD, CYAN, RESET);
		indent(c, size);
		print_char(' ', g_minishell.tab_indentation);
		c = printf("|%s%s     %s%s", BOLD, CYAN, node->subshell, RESET);
		indent(c, size);
	}
}

void	module_argv(char **matrix, int size)
{
	int	i;
	int	c;

	i = 0;
	if (matrix[i] && matrix[i][0])
	{
		print_char(' ', g_minishell.tab_indentation);
		divider('-', size);
		while (matrix[i])
		{
			print_char(' ', g_minishell.tab_indentation);
			c = printf("|  %sArgs[%d]: %s%s%s", BOLD, i, CYAN, \
			matrix[i], RESET);
			indent(c, size);
			i++;
		}
	}
}

void	footer_box(int size)
{
	print_char(' ', g_minishell.tab_indentation);
	divider('_', size);
}
