/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:07:20 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/24 20:59:39 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell g_minishell;

void	handle_operators(void)
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
				parent(node, fd);
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
		handle_operators();
	waitpid(id, &status, 0);
	g_minishell.node = 0;
	/* while (g_minishell.node)
	{
		printf("nome do comando: %s, relação com o proximo comando: %s\n", g_minishell.node->full_instruction, g_minishell.node->relation);
		g_minishell.node = g_minishell.node->next;
	} */
}
