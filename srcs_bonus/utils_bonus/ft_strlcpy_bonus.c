/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:53:29 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:53:30 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

void	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (!src || !dst)
		return ;
	while (src[index] && index + 1 < size)
	{
		dst[index] = src[index];
		index++;
	}
	if (size > 0)
		dst[index] = '\0';
}
