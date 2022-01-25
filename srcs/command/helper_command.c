/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:53:32 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/25 10:16:42 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell g_minishell;

t_node	*add_new_cmd(char *command, char *relation)
{
	t_node	*begin;
	t_node	*new_cmd;

	new_cmd = (t_node *) ft_calloc(1, sizeof(t_node));
	new_cmd->full_instruction = ft_strtrim(command, " ");
	new_cmd->full_instruction = swap_chars(new_cmd->full_instruction, ' ', 1);
	new_cmd->argv = ft_split(new_cmd->full_instruction, ' ');
	new_cmd->argv = search_matrix(new_cmd->argv);
	new_cmd->argv = trim_quotes(new_cmd->argv);
	new_cmd->input = STDIN_FILENO;
	new_cmd->output = STDOUT_FILENO;
	new_cmd->relation = relation;
	begin = g_minishell.node;
	if (begin == 0)
		g_minishell.node = new_cmd;
	else
	{
		while (begin->next)
			begin = begin->next;
		new_cmd->previous = begin;
		begin->next = new_cmd;
	}
	return (new_cmd);
}

void	check_command_exist(t_node *cmd)
{
	char	*cmd_path;
	char	*tmp;
	int		index;
	int		exist;

	index = 0;
	exist = 0;
	while (g_minishell.paths[index] != 0)
	{
		tmp = ft_strjoin(g_minishell.paths[index], "/");
		cmd_path = ft_strjoin(tmp, cmd->argv[0]);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
		{
			free(cmd->argv[0]);
			cmd->argv[0] = cmd_path;
			exist = 1;
			break ;
		}
		else
			free(cmd_path);
		index++;
	}
	if (exist == 0)
		cmd->not_exist = 1;
}

void	execute_cmd(t_node *cmd)
{
	if (cmd->not_exist == 1)
		exit(1);
	execve(cmd->argv[0], cmd->argv, NULL);
}

void	last_child(t_node *node)
{
	execute_cmd(node);
	exit(0);
}

void	parent(t_node *cmd, int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	execute_cmd(cmd);
	exit(0);
}
