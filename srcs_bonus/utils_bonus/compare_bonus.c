/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:52:59 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

static int	filter_size(char *filter)
{
	int	index;

	index = 0;
	while (filter[index] && filter[index] != '*')
		index++;
	return (index);
}

static char	*string_forward(char *string, char *filter)
{
	while ((ft_strncmp(string, filter, filter_size(filter)) \
	|| *filter == '\0') && *string)
		string++;
	return (string);
}

int	compare(char *string, char *filter)
{
	int	index;

	index = 0;
	while (string[index])
	{
		if (*filter == '*')
		{
			while (*filter == '*')
				filter++;
			string = string_forward(&string[index], filter);
			index = 0;
		}
		if (string[index] != *filter)
			return (0);
		if (!string[index] || !*filter)
			break ;
		filter++;
		index++;
	}
	while (*filter == '*')
		filter++;
	if ((*filter != '\0' && string[index] == '\0') || \
	(*filter == '\0' && string[index] != '\0'))
		return (0);
	return (1);
}
