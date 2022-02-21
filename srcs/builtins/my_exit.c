/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:45:04 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell	g_minishell;

void	my_exit(char **argv)
{
	int	status;

	printf("exit\n");
	if (argv != 0)
	{
		if (argv[1] && argv[2])
		{
			show_error("exit: ", "too many arguments", 1, 0);
			g_minishell.exit_code = 1;
			return ;
		}
		if (argv[1])
		{
			status = ft_atoi(argv[1]);
			clean_trash();
			exit(status);
		}
	}
	clean_trash();
	exit(g_minishell.exit_code);
}
