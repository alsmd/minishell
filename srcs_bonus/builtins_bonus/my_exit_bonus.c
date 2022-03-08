/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:49:24 by flda-sil          #+#    #+#             */
/*   Updated: 2022/03/08 15:36:51 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

int	check_argv(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!is_number(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	set_status(char *argv)
{
	char	*buffer;
	int		status;

	if (check_argv(argv))
	{
		buffer = ft_strdup(argv);
		buffer = ft_strjoin(buffer, ": numeric argument required");
		show_error("exit: ", buffer, 1, 0);
		status = 2;
		free(buffer);
	}
	else
		status = ft_atoi(argv);
	return (status);
}

void	my_exit(char **argv)
{
	int		status;

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
			status = set_status(argv[1]);
			clean_trash();
			exit(status);
		}
	}
	clean_trash();
	exit(g_minishell.exit_code);
}
