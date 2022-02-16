/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:47:01 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:47:02 by flda-sil            ###   ########.fr       */
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
