/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:43:55 by flavio            #+#    #+#             */
/*   Updated: 2022/02/02 13:46:38 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;

	r = malloc(nmemb * size);
	if (r)
	{
		ft_bzero(r, nmemb * size);
		return (r);
	}
	return (0);
}
