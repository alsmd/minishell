/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relations_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:50:08 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	fill_missing_arg(char *buffer, char *relation)
{
	char	**argv;
	char	*tmp;
	int		index;

	tmp = buffer;
	index = 0;
	if (!relation || !is_redirect(relation))
	{
		free(tmp);
		return ;
	}
	while (!is_in(g_minishell.operators, &buffer[index]) && buffer[index])
		index++;
	buffer[index] = '\0';
	while (*buffer == ' ')
		buffer++;
	while (*buffer != ' ' && *buffer != '\0')
		buffer++;
	if (*buffer != '\0')
	{
		argv = ft_split(buffer, ' ');
		g_minishell.node->argv = merge_matriz(g_minishell.node->argv, argv);
	}
	free(tmp);
}

char	*check_relation(char *buffer, int *index, int quoute, int *first)
{
	char	*relation;

	if (buffer[*index] == '(' && !quoute)
	{
		buffer = create_subshell(&buffer[*index]);
		*index = 0;
		return (buffer);
	}
	relation = is_in(g_minishell.operators, &(buffer[*index]));
	if (relation && !quoute)
	{	
		buffer = create_node(buffer, first, *index, relation);//cat <<      file1 file2 file3 NULL aokd > ola
		fill_missing_arg(ft_strdup(buffer), relation);
		*index = 0;
	}
	else
		*index += 1;
	return (buffer);
}

void	create_relations(char *buffer)
{
	int		index;
	int		first;
	char	quoute_is_on;

	quoute_is_on = 0;
	index = 0;
	first = TRUE;
	while (buffer[index])
	{
		toggle_quoute(&buffer[index], &quoute_is_on);
		buffer = check_relation(buffer, &index, quoute_is_on, &first);
	}
	if (*buffer != 0)
		add_new_cmd(buffer, 0);
	toogle_space(0);
}

void	link_relations(void)
{
	t_node	*node;

	node = g_minishell.node;
	while (node)
	{
		if (node->relation == 0)
			break ;
		else if (!ft_strncmp(node->relation, "|", -1))
			handle_pipe(node);
		else if (node->relation[0] == '>')
			handle_output(node);
		else if (node->relation[0] == '<' && node->relation[1] == '\0')
			handle_input(node);
		else if (!ft_strncmp(node->relation, "<<", 2))
			handle_here_doc(node);
		node = node->next;
	}
}
