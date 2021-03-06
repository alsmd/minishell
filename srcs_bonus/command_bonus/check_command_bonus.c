/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:49:38 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	check_absolute_path(t_node *cmd)
{
	cmd->is_absolute_path = TRUE;
	if (!ft_strncmp(cmd->argv[0], "/", -1))
		cmd->not_exist = 1;
	else if (access(cmd->argv[0], F_OK) == 0)
	{
		cmd->not_exist = 0;
		if (access(cmd->argv[0], X_OK) == 0)
			cmd->is_executable = 1;
	}
	else
		cmd->not_exist = 1;
}

void	check_command_exist(t_node *cmd)
{
	char	*cmd_path;
	char	*tmp;
	int		index;
	int		exist;

	index = -1;
	exist = 0;
	if (!cmd->argv[0])
		return ;
	while (g_minishell.paths && g_minishell.paths[++index] != 0)
	{
		tmp = ft_strjoin(ft_strdup(g_minishell.paths[index]), "/");
		cmd_path = ft_strjoin(tmp, cmd->argv[0]);
		if (access(cmd_path, F_OK) == 0)
		{
			free(cmd->full_path);
			cmd->full_path = cmd_path;
			exist = 1;
			break ;
		}
		else
			free(cmd_path);
	}
	if (exist == 0)
		cmd->not_exist = 1;
}

int	is_command(t_node *node)
{
	if (node->previous == 0 && node->argv[0])
		return (1);
	if (node->previous == 0)
		return (0);
	if (node->previous->relation && node->previous->relation[0] == '|')
		return (1);
	if (node->previous->relation && node->previous->relation[0] == '&')
		return (1);
	if (node->previous->relation && node->previous->relation[0] == ' ')
		return (1);
	if (node->relation == 0 && node->previous->relation[0] == '|')
		return (1);
	return (0);
}
