/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:52:28 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	find_result(char *filter, t_node *node, int *limiter)
{
	g_minishell.only_dir = FALSE;
	if (g_minishell.asterisk_buffer)
		free(g_minishell.asterisk_buffer);
	g_minishell.asterisk_buffer = ft_strdup("");
	get_asterisk_buffer(filter, ft_strjoin(get_var_value("PWD"), "/"));
	if (g_minishell.asterisk_found > 0)
	{
		node->argv = join_matriz(node->argv, \
			ft_split(g_minishell.asterisk_buffer, ' '), limiter);
	}
}

int	expand_asterisk(char *buffer, t_node *node, int *limiter)
{
	int		index;
	char	quoute_is_on;

	index = 0;
	quoute_is_on = 0;
	g_minishell.asterisk_found = 0;
	while (buffer[index])
	{
		toggle_quoute(&buffer[index], &quoute_is_on);
		if (quoute_is_on == 0 && buffer[index] == '*')
		{
			find_result(buffer, node, limiter);
			break ;
		}
		if (buffer[index])
			index++;
	}
	if (g_minishell.asterisk_found)
		free(buffer);
	return (g_minishell.asterisk_found);
}
