/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:42:07 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/04 09:28:18 by gsilva-v         ###   ########.fr       */
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
