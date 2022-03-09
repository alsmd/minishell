/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:49:07 by flda-sil          #+#    #+#             */
/*   Updated: 2022/03/09 09:09:52 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	my_echo(char **argv)
{
	int	broke_line;
	int	i;

	i = 1;
	broke_line = 0;
	if (argv[1] && !ft_strncmp(argv[1], "-n", -1))
	{
		broke_line = 1;
		i = 2;
		while (!ft_strncmp(argv[i], "-n", -1))
			i++;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (broke_line == 0)
		write (1, "\n", 1);
	g_minishell.exit_code = 0;
}
