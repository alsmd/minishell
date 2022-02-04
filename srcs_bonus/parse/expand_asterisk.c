#include <minishell_bonus.h>

extern t_minishell	g_minishell;

int		get_filter_size(char *buffer)
{
	int	index;

	index = 0;
	while (buffer[index] && buffer[index] != ' ')
		index++;
	return (index);
}

char	*get_filter(char *buffer, int index)
{
	char	*new_buffer;
	int		size;

	size = 0;
	while (buffer[index] != ' ' && index)//echo ola*
		index--;
	size = get_filter_size(&buffer[index]);
	new_buffer = (char *) ft_calloc(size + 1, sizeof(char));
	size = 0;
	if (buffer[index] == ' ')
		index++;
	while (buffer[index] && buffer[index] != ' ')
	{
		new_buffer[size] = buffer[index];
		index++;
		size++;
	}
	return (new_buffer);
}

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

int	matriz_size(char **m)
{
	int	index;

	index = 0;
	while (m[index])
		index++;
	return (index);
}

// Cola a m2 no index "limiter" da m1 retorna o index correspondente ao proximo elemento depois da m2

char	**join_matriz(char **m1, char **m2, int *limiter)
{
	int		index;
	int		m1_index;
	int		m2_index;
	int		size;
	char	**new_matriz;

	m1_index = 0;
	m2_index = 0;
	index = 0;
	size = matriz_size(m1) + matriz_size(m2);
	new_matriz = (char **) ft_calloc(size, sizeof(char *));
	while (index < *limiter)
	{
		new_matriz[index] = m1[index];
		index++;
	}
	m1_index += index + 1;
	while (m2[m2_index])
	{
		new_matriz[index] = m2[m2_index];
		m2_index += 1;
		index++;
	}
	*limiter = index;
	while (m1[m1_index])
	{
		new_matriz[index] = m1[m1_index];
		m1_index++;
		index++;
	}
	free(m1);
	free(m2);
	return (new_matriz);
}


int	expand_asterisk(char *buffer, t_node *node, int *limiter)
{
	char	*filter;
	int		index;
	int		j;
	char	quoute_is_on;

	index = 0;
	j = 0;
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
		{
			filter = get_filter(buffer, index);
			fflush(stdout);
			if (g_minishell.asterisk_buffer)
				free(g_minishell.asterisk_buffer);
			g_minishell.asterisk_buffer = ft_strdup("");
			get_asterisk_buffer(filter, ft_strjoin(get_var_value("PWD"), "/"));
			if (g_minishell.asterisk_found > 0)
				node->argv = join_matriz(node->argv, ft_split(g_minishell.asterisk_buffer, ' '), limiter);
			index += custom_size_after(filter);
			free(filter);
		}
		if (buffer[index])
			index++;
	}
	if (g_minishell.asterisk_found)
		free(buffer);
	return (g_minishell.asterisk_found);
}