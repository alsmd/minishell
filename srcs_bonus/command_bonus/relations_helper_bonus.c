#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	toogle_space(int on)
{
	char	*tmp;

	if (on == 0 && g_minishell.operators[7])
	{
		tmp = g_minishell.operators[7];
		g_minishell.operators[7] = NULL;
		g_minishell.operators[8] = tmp;
	}
	else if (on)
	{
		tmp = g_minishell.operators[8];
		g_minishell.operators[7] = tmp;
		g_minishell.operators[8] = NULL;
	}
}

static int	get_buffer_len(char *buffer)
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

char	*create_node(char *buffer, int *first, int index, char *relation)
{
	toogle_space(0);
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
	if (*first == TRUE && g_minishell.node->argv[0] == 0)
	{
		while (*buffer && *buffer == ' ')
			buffer++;
		toogle_space(1);
	}
	*first = FALSE;
	return (buffer);
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
		buffer += ft_strlen(relation);
	node = add_new_cmd("subshell", relation);
	node->subshell = sub_buffer;
	return (buffer);
}

void	set_signal(int *status)
{
	if (g_minishell.has_signal)
		*status = g_minishell.exit_code;
	else
		*status = get_status(*status);
	if (*status == 131)
		write(1, "Quit (core dumped)\n", 20);
	if (*status == 130)
		write(1, "\n", 1);
	if (*status == 130 || *status == 131)
	{
		clean_trash();
		exit(*status);
	}
}