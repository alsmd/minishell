/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:07:20 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/24 20:38:39 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
extern t_minishell g_minishell;


t_node	*add_new_cmd(char *command, char *relation)
{
	t_node	*begin;
	t_node	*new_cmd;

	new_cmd = (t_node *) ft_calloc(1, sizeof(t_node));
	new_cmd->argv = ft_split(command, ' ');
	new_cmd->full_instruction = command;
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

void	execute_cmd(t_node *cmd, char *env[])
{
	if (cmd->not_exist == 1)
		exit(1);
	execve(cmd->argv[0], cmd->argv, env);
}

void	last_child(t_node *node)
{
	execute_cmd(node, g_minishell.env);
	exit(0);
}

void	parent(t_node *cmd, char *env[], int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	execute_cmd(cmd, env);
	exit(0);
}

void	start_pipex(void)
{
	t_node		*node;
	int			id;
	int			fd[2];
	int			status;

	node = g_minishell.node;
	while (node->next)
		node = node->next;
	while (node->previous)
	{
		if (node->previous->relation[0] == '|')
		{
			if (pipe(fd) == -1)
				return ;
			id = fork();
			if (id == -1)
				return ;
			if (id != 0)
			{
				waitpid(id, &status, 0);
				parent(node, g_minishell.env, fd);
			}
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
		}
		else if (node->previous->relation[0] == '>')
			output(node);
		node = node->previous;
	}
	last_child(node);
}

void	make_shell_command(char *buffer)
{
	char		*relation;
	int			index;
	int			id;
	int			status;

	/*
		Percorre a string referente ao comando, ex: ls -l | grep d | wc -l > exit,
		e coloca cada comando em um node da lista encadeada armazenando o relacionamento com o proximo comando.
	*/
	index = 0;
	while (buffer[index])
	{
		relation = is_in(g_minishell.operators, &(buffer[index]));
		if (relation)
		{	
			if (!ft_strncmp(&buffer[index], ">>", 2) || !ft_strncmp(&buffer[index], "<<", 2))
			{
				buffer[index] = '\0';
				index++;
			}
			buffer[index] = '\0';
			index++;
			add_new_cmd(buffer, relation);
			buffer += index;
			index = 0;
		}
		else
			index++;
	}
	if (*buffer != 0)
		add_new_cmd(buffer, 0);
	id = fork();
	if (id == 0)
		start_pipex();
	waitpid(id, &status, 0);
	g_minishell.node = 0;
	/* while (g_minishell.node)
	{
		printf("nome do comando: %s, relação com o proximo comando: %s\n", g_minishell.node->full_instruction, g_minishell.node->relation);
		g_minishell.node = g_minishell.node->next;
	} */
}
