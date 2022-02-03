/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 18:42:07 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/03 04:09:01 by flda-sil         ###   ########.fr       */
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
	return (0);
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
