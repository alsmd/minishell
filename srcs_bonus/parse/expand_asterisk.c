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
char	*expand_asterisk(char *buffer)
{
	char	*new_buffer;
	char	*filter;
	int		index;
	int		j;
	char	quoute_is_on;

	index = 0;
	j = 0;
	quoute_is_on = 0;
	new_buffer = ft_strdup(buffer);
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
			g_minishell.asterisk_found = 0;
			get_asterisk_buffer(filter, get_var_value("PWD"));
			if (g_minishell.asterisk_found > 0)
			{
				new_buffer[index + j - custom_size_before(filter)] = '\0';
				new_buffer = ft_strjoin(new_buffer, g_minishell.asterisk_buffer);
				j += ft_strlen(g_minishell.asterisk_buffer);
			}
			index += custom_size_after(filter);
		}
		index++;
	}
	free(buffer);
	return (new_buffer);
}