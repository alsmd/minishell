/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:47:12 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strdup(const char *s)
{
	char	*cpy;
	size_t	size;
	size_t	index;

	index = 0;
	size = ft_strlen(s) + 1;
	cpy = (char *) ft_calloc(size, 1);
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
