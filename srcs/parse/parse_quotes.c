/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:43:26 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/01/25 09:24:36 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *swap_chars(char *cmd, char to_find, char to_put)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\'' && cmd[i] != '\"' && cmd[i])
			{
				if (cmd[i] == to_find)
					cmd[i] = to_put;
				i++;
			}
		}
		i++;
	}
	return (cmd);
}

char **search_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
	{
		matrix[i] = swap_chars(matrix[i], 1, ' ');
		i++;
	}
	return (matrix);
}

char **trim_quotes(char **matrix)
{
	int i;
	
	i = 0;
	while (matrix[i])
	{
		
		if (matrix[i][0] == '\'')
			matrix[i] = ft_strtrim(matrix[i], "\'");
		else
			matrix[i] = ft_strtrim(matrix[i], "\"");
		i++;
	}
	return (matrix);
}

int is_comand(char *s)
{
	char *cmd;
	char **matrix;
	char *temp;

	
	temp = swap_chars(s, ' ', 1);
	matrix = ft_split(temp, ' ');
	matrix = search_matrix(matrix);
	matrix = trim_quotes(matrix);
//coloar a trim de aspas aqui
//chegar se é builtin ou se é comando
	// cmd = check_access(matrix[0]);

	// if (cmd == NULL)
	// 	return (1);
	return (0);
}