/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:52:44 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:52:45 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

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

char	*copy_string_trim(char *string)
{
	int		i;
	int		desloc;
	char	*tmp;
	int		is_active;
	char	quoute;

	quoute = 0;
	is_active = FALSE;
	tmp = (char *) ft_calloc(ft_strlen(string) + 1, sizeof(char));
	i = 0;
	desloc = 0;
	while (string[i + desloc])
	{
		if (check_quoute(string[i + desloc], &is_active, &quoute))
		{
			tmp[i] = string[i + desloc];
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

	j = 0;
	while (matrix[j])
	{
		tmp = copy_string_trim(matrix[j]);
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
