/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 19:43:55 by flavio            #+#    #+#             */
/*   Updated: 2022/01/18 17:55:35 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;

	if (nmemb * size > INT_MAX)
	{
		errno = 12;
		return (0);
	}
	r = malloc(nmemb * size);
	if (r)
	{
		ft_bzero(r, nmemb * size);
		return (r);
	}
	return (0);
}
