/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:52:51 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

int	found_operator_right(char *buffer, int index)
{
	while (buffer[index])
	{
		if (buffer[index] == ')' || buffer[index] == '(')
		{
			index++;
			continue ;
		}
		if (is_in(g_minishell.operators, &(buffer[index])))
			return (1);
		if (buffer[index] != ' ')
			return (0);
		index++;
	}
	return (1);
}

int	found_operator_left(char *buffer, int index)
{
	char	*relation;

	while (index >= 0 && buffer[index])
	{
		if (buffer[index] == ')' || buffer[index] == '(')
		{
			index--;
			continue ;
		}
		if (is_in(g_minishell.operators, &(buffer[index])))
			return (1);
		if (index - 1 >= 0)
		{
			relation = is_in(g_minishell.operators, &(buffer[index - 1]));
			if (relation && ft_strlen(relation) == (size_t) 2)
				return (1);
		}
		if (buffer[index] != ' ')
			return (0);
		index--;
	}
	return (1);
}

int	another_parenthesis(char *buffer, int index)
{
	while (buffer[index])
	{
		if (buffer[index] == '(')
			return (1);
		if (buffer[index] != ' ')
			return (0);
		index += 1;
	}
	return (0);
}

char	*swap_chars(char *cmd, char to_find, char to_put)
{
	int		i;
	char	quote_is_on;

	quote_is_on = FALSE;
	i = 0;
	while (cmd[i])
	{
		toggle_quoute(&cmd[i], &quote_is_on);
		if (quote_is_on)
		{
			i++;
			while (quote_is_on && cmd[i])
			{
				if (cmd[i] == to_find)
					cmd[i] = to_put;
				i++;
				toggle_quoute(&cmd[i], &quote_is_on);
			}
		}
		if (cmd[i])
			i++;
	}
	return (cmd);
}

char	**search_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		matrix[i] = swap_chars(matrix[i], 1, ' ');
		i++;
	}
	return (matrix);
}
