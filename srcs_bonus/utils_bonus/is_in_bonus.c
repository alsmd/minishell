/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:54:01 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:54:02 by flda-sil            ###   ########.fr       */
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
