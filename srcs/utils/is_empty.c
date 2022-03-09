/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:10:11 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/03/09 09:10:12 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_empty(char *buffer)
{
	while (*buffer)
	{
		if (!is_space(*buffer))
			return (0);
		buffer++;
	}
	return (1);
}
