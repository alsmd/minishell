/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:46:41 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_quoute(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	check_quoute(char c, int *is_active, char *quoute)
{
	if (!*is_active && is_quoute(c) && c != *quoute)
	{
		*quoute = c;
		*is_active = TRUE;
		return (0);
	}
	if (*is_active == TRUE && c == *quoute)
	{
		*quoute = 0;
		*is_active = FALSE;
		return (0);
	}
	return (1);
}

char	*copy_string_trim(char **matrix, int j, int *is_active, char *quoute)
{
	int		i;
	int		desloc;
	char	*tmp;

	tmp = (char *) ft_calloc(ft_strlen(matrix[j]) + 1, sizeof(char));
	i = 0;
	desloc = 0;
	while (matrix[j][i + desloc])
	{
		if (check_quoute(matrix[j][i + desloc], is_active, quoute))
		{
			tmp[i] = matrix[j][i + desloc];
			i++;
		}
		else
			desloc++;
	}
	return (tmp);
}

void	trim_quotes(char **matrix)
{
	char	*tmp;
	int		j;
	int		is_active;
	char	quoute;

	j = 0;
	quoute = 0;
	is_active = FALSE;
	while (matrix[j])
	{
		tmp = copy_string_trim(matrix, j, &is_active, &quoute);
		free(matrix[j]);
		matrix[j] = tmp;
		j++;
	}
}

void	toggle_quoute(char *buffer, char *quoute_is_on)
{
	if (*buffer == '\'' || *buffer == '"')
	{
		if (!*quoute_is_on)
			*quoute_is_on = *buffer;
		else if (*quoute_is_on && *buffer == *quoute_is_on)
			*quoute_is_on = FALSE;
	}
}
