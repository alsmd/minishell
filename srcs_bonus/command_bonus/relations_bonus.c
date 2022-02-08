#include <minishell_bonus.h>

extern t_minishell	g_minishell;

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
		if (buffer[index] == '(' && !quoute_is_on)
		{
			buffer = create_subshell(&buffer[index]);
			index = 0;
			continue ;
		}
		if (is_in(g_minishell.operators, &(buffer[index])) && !quoute_is_on)
		{	
			buffer = create_node(buffer, &first, index, \
			is_in(g_minishell.operators, &(buffer[index])));
			index = 0;
		}
		else
			index++;
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
