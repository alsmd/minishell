/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:46:32 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:46:33 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell	g_minishell;

int	check_next_relation(t_node *node)
{
	if (node->relation && (!node->next || \
	!node->next->argv || !node->next->argv[0]))
	{
		if (!ft_strncmp(node->relation, "|", 1))
			show_error(M_ERROR_SINTAX, node->relation, 2, 0);
		else
			show_error(M_ERROR_SINTAX, "'newline'", 2, 0);
		return (1);
	}
	return (0);
}

int	check_next_file(t_node *node)
{
	if (node->relation && (!ft_strncmp(node->relation, ">", -1) || \
	!ft_strncmp(node->relation, ">>", -1)) && node->next && \
	node->next->argv && !ft_strncmp(node->next->argv[0], "/", -1))
	{
		printf("%s\033[33m☣\033[0m\n", M_UNK);
		return (1);
	}
	return (0);
}

int	check_grammar(void)
{
	t_node	*init;

	init = g_minishell.node;
	while (init)
	{
		if (check_next_file(init) || check_next_relation(init))
			return (1);
		init = init->next;
	}
	return (0);
}
