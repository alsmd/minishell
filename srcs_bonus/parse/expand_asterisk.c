#include <minishell_bonus.h>

extern t_minishell	g_minishell;

int	custom_size_after(char *filter)
{
	int	index;

	index = 0;
	while (*filter && *filter != '*')
		filter++;
	while (filter[index])
		index++;
	return (index);
}

int	custom_size_before(char *filter)
{
	int	index;

	index = 0;
	while (filter[index] && filter[index] != '*')
		index++;
	return (index);
}

void	find_result(char *buffer, t_node *node, int index, int *limiter)
{
	char	*filter;

	filter = get_filter(buffer, index);
	if (g_minishell.asterisk_buffer)
		free(g_minishell.asterisk_buffer);
	g_minishell.asterisk_buffer = ft_strdup("");
	get_asterisk_buffer(filter, ft_strjoin(get_var_value("PWD"), "/"));
	if (g_minishell.asterisk_found > 0)
			node->argv = join_matriz(node->argv,
				ft_split(g_minishell.asterisk_buffer, ' '), limiter);
	index += custom_size_after(filter);
	free(filter);
}

int	expand_asterisk(char *buffer, t_node *node, int *limiter)
{
	int		index;
	char	quoute_is_on;

	index = 0;
	quoute_is_on = 0;
	g_minishell.asterisk_found = 0;
	while (buffer[index])
	{
		if (buffer[index] == '\'' || buffer[index] == '"')
		{
			if (!quoute_is_on)
				quoute_is_on = TRUE;
			else if (quoute_is_on && buffer[index] == quoute_is_on)
				quoute_is_on = FALSE;
		}
		if (quoute_is_on == 0 && buffer[index] == '*')
			find_result(buffer, node, index, limiter);
		if (buffer[index])
			index++;
	}
	if (g_minishell.asterisk_found)
		free(buffer);
	return (g_minishell.asterisk_found);
}
