/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:44:53 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(t_node *cmd)
{
	if (!cmd->argv[0])
		return (FALSE);
	if (!(ft_strncmp(cmd->argv[0], "exit", -1)))
		return (TRUE);
	if (!(ft_strncmp(cmd->argv[0], "cd", -1)))
		return (TRUE);
	if (!(ft_strncmp(cmd->argv[0], "pwd", -1)))
		return (TRUE);
	if (!(ft_strncmp(cmd->argv[0], "export", -1)))
		return (TRUE);
	if (!(ft_strncmp(cmd->argv[0], "env", -1)))
		return (TRUE);
	if (!(ft_strncmp(cmd->argv[0], "unset", -1)))
		return (TRUE);
	if (!(ft_strncmp(cmd->argv[0], "echo", -1)))
		return (TRUE);
	if (!(ft_strncmp(cmd->argv[0], "color", -1)))
		return (TRUE);
	return (FALSE);
}

void	exec_builtin(t_node *cmd)
{
	if (cmd->argv)
	{
		if (!(ft_strncmp(cmd->argv[0], "exit", -1)))
			my_exit(cmd->argv);
		if (!(ft_strncmp(cmd->argv[0], "echo", -1)))
			my_echo(cmd->argv);
		if (!(ft_strncmp(cmd->argv[0], "cd", -1)))
			cd(cmd->argv);
		if (!(ft_strncmp(cmd->argv[0], "pwd", -1)))
			pwd();
		if (!(ft_strncmp(cmd->argv[0], "export", -1)))
			export(cmd->argv[1]);
		if (!(ft_strncmp(cmd->argv[0], "env", -1)))
			env();
		if (!(ft_strncmp(cmd->argv[0], "unset", -1)))
			unset(cmd->argv[1]);
		if (!(ft_strncmp(cmd->argv[0], "color", -1)))
			set_color(cmd->argv[1]);
	}
}
