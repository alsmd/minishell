/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:43:06 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/26 08:56:54 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <errno.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*cpy;
	size_t	size;
	size_t	index;

	index = 0;
	size = ft_strlen(s) + 1;
	cpy = (char *) malloc(size);
	if (!(cpy))
		return (0);
	while (s[index])
	{
		cpy[index] = s[index];
		index++;
	}
	cpy[index] = '\0';
	return (cpy);
}
