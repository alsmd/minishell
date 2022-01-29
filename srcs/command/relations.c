#include <minishell.h>

extern t_minishell	g_minishell;

char	*create_node(char *buffer, int first, int index, char *relation)
{
	if (relation[0] == ' ')
		g_minishell.operators[7] = NULL;
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
		g_minishell.operators[7] = " ";
		g_minishell.operators[8] = NULL;
	}
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
