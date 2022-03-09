/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:53:02 by flda-sil          #+#    #+#             */
/*   Updated: 2022/03/08 15:35:32 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	is_number(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	get_overflow_n(int sign)
{
	if (sign == 1)
		return (-1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	size_t		index;
	int			sign;
	int			re;

	sign = 1;
	re = 0;
	index = 0;
	while (is_space(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (is_number(nptr[index]))
	{
		if (index >= 18)
			return (get_overflow_n(sign));
		re = (re * 10) + (nptr[index++] - 48);
	}
	return (re * sign);
}
