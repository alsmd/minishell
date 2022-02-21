/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:54:01 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

char	*is_in(char **array, char *str)
{
	while (*array)
	{
		if (!ft_strncmp(*array, str, ft_strlen(*array)))
			return (*array);
		array++;
	}
	return (NULL);
}

int	has(char *string, char c)
{
	while (*string)
	{
		if (*string == c)
			return (1);
		string++;
	}
	return (0);
}
