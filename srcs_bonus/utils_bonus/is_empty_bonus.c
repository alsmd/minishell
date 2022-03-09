/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 09:10:03 by gsilva-v          #+#    #+#             */
/*   Updated: 2022/03/09 09:10:04 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

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
