/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:07:20 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/24 21:42:54 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell g_minishell;

void	handle_operators(void)
{
	t_node		*node;

	node = g_minishell.node;
	while (node->next)
		node = node->next;
	while (node->previous)
	{
		if (node->previous->relation[0] == '|')
			handle_pipe(node);
		else if (node->previous->relation[0] == '>')
			handle_output(node);
		node = node->previous;
	}
	last_child(node);
}

/*
	Percorre a string referente ao comando, ex: ls -l | grep d | wc -l > exit,
	e coloca cada comando em um node da lista encadeada armazenando o relacionamento com o proximo comando.
*/

void	create_relations(char *buffer)
{
	char		*relation;
	int			index;

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
}

void	make_shell_command(char *buffer)
{
	int			id;
	int			status;

	create_relations(buffer);
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
