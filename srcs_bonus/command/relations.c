#include <minishell_bonus.h>

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
	!ft_strncmp(&buffer[index], "<<", 2) || \
	!ft_strncmp(&buffer[index], "&&", 2) || \
	!ft_strncmp(&buffer[index], "||", 2))
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

int	get_buffer_len(char *buffer)
{
	int	index;
	int	count;

	index = 1;
	count = 1;
	while (buffer[index])
	{
		if (buffer[index] == '(')
			count++;
		if (buffer[index] == ')')
			count--;
		if (!count)
			break ;
		index++;
	}
	return (index);
}

char	*create_subshell(char *buffer)
{
	t_node	*node;
	char	*relation;
	char	*sub_buffer;

	sub_buffer = (char *) ft_calloc(get_buffer_len(buffer), sizeof(char));
	ft_strlcpy(sub_buffer, &buffer[1], get_buffer_len(buffer));
	buffer += get_buffer_len(buffer) + 1;
	relation = is_in(g_minishell.operators, buffer);
	while (*buffer && !relation)
	{
		buffer++;
		relation = is_in(g_minishell.operators, buffer);
	}
	if (*buffer)
		buffer++;
	node = add_new_cmd("subshell", relation);
	node->subshell = sub_buffer;
	return (buffer);
}

void	create_relations(char *buffer)
{
	char	*relation;
	int		index;
	int		first;

	index = 0;
	first = TRUE;
	while (buffer[index])
	{
		if (buffer[index] == '(')
		{
			buffer = create_subshell(&buffer[index]);
			index = 0;
			continue ;
		}
		relation = is_in(g_minishell.operators, &(buffer[index]));
		if (relation)
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

void	link_relations(t_node *node)
{
	if (!node)
		node = g_minishell.node;
	while (node)
	{
		if (node->relation == 0)
			break ;
		else if (!ft_strncmp(node->relation, "||", 2))
		{
			link_relations(node->next);
			break ;
		}
		else if (!ft_strncmp(node->relation, "|", 2))
			handle_pipe(node);
		else if (node->relation[0] == '>')
			handle_output(node);
		else if (node->relation[0] == '<' \
		&& node->relation[1] == '\0')
			handle_input(node);
		else if (!ft_strncmp(node->relation, "<<", 2))
			handle_here_doc(node);
		else if (!ft_strncmp(node->relation, "&&", 2))
		{
			link_relations(node->next);
			break ;
		}
		node = node->next;
	}
}
