/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:45:36 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell	g_minishell;

void	turn_off_space(void)
{
	char	*tmp;

	if (g_minishell.operators[7] != NULL)
	{
		tmp = g_minishell.operators[7];
		g_minishell.operators[7] = NULL;
		g_minishell.operators[8] = tmp;
	}
}

char	*create_node(char *buffer, int first, int index, char *relation)
{
	char	*tmp;

	turn_off_space();
	if (!ft_strncmp(&buffer[index], ">>", 2) || \
	!ft_strncmp(&buffer[index], "<<", 2))
	{
		buffer[index] = '\0';
		index++;
	}
	buffer[index] = '\0';
	index++;
	add_new_cmd(buffer, relation);
	buffer += index;
	if (first == TRUE && g_minishell.node->argv[0] == 0)
	{
		while (*buffer && *buffer == ' ')
			buffer++;
		tmp = g_minishell.operators[8];
		g_minishell.operators[7] = tmp;
		g_minishell.operators[8] = NULL;
	}
	return (buffer);
}

void	create_relations(char *buffer)
{
	char	*relation;
	int		index;
	int		first;
	char	quoute_is_on;

	quoute_is_on = 0;
	index = 0;
	first = TRUE;
	while (buffer[index])
	{
		toggle_quoute(&buffer[index], &quoute_is_on);
		relation = is_in(g_minishell.operators, &(buffer[index]));
		if (relation && !quoute_is_on)
		{	
			buffer = create_node(buffer, first, index, relation);
			index = 0;
			first = FALSE;
		}
		else
			index++;
	}
	if (*buffer != 0)
		add_new_cmd(buffer, 0);
	turn_off_space();
}

void	link_relations(void)
{
	t_node	*node;

	node = g_minishell.node;
	while (node)
	{
		if (node->relation == 0)
			break ;
		if (node->relation[0] == '|')
			handle_pipe(node);
		else if (node->relation[0] == '>')
			handle_output(node);
		else if (node->relation[0] == '<' \
		&& node->relation[1] == '\0')
			handle_input(node);
		else if (!ft_strncmp(node->relation, "<<", 2))
			handle_here_doc(node);
		node = node->next;
	}
}
