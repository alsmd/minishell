#include <minishell_bonus.h>

extern t_minishell	g_minishell;

int	get_variable_len(char *key)
{
	int	i;

	i = 0;
	while (key[i] && key[i] != ' ' && key[i] != '\'' && key[i] != '\"')
		i++;
	return (i);
}

int	toogle_value(int signal)
{
	if (signal == 0)
		return (TRUE);
	return (FALSE);
}

static void	cut_char(char *buffer)
{
	int	index;
	int	is_in_quotes;

	is_in_quotes = FALSE;
	index = 0;
	while (buffer[index])
	{
		if (buffer[index] == '\"')
			is_in_quotes = toogle_value(is_in_quotes);
		if (buffer[index] == '\'' && is_in_quotes == FALSE)
		{
			index++;
			while (buffer[index] != '\'' && buffer[index])
				index++;
		}
		if (buffer[index] == '$')
		{
			buffer[index] = 0;
			break ;
		}
		index++;
	}
}

char	*write_variable(char *new_buffer, char *buffer, int index)
{
	char	*value;

	//limitando o tamanho para o join, colocando byte nulo ante do $
	cut_char(new_buffer);
	value = get_var_value(&buffer[index + 1]);
	new_buffer = ft_strjoin(new_buffer, value);
	new_buffer = ft_strjoin(new_buffer, \
	&buffer[index + get_variable_len(&buffer[index])]);
	free (value);
	return (new_buffer);
}

char	*get_filter(char *buffer, int index)
{
	char	*new_buffer;
	int		size;

	size = 0;
	while (buffer[index] != ' ' && index)//echo ola*
	{
		size++;
		index--;
	}
	new_buffer = (char *) ft_calloc(size + 1, sizeof(char));
	size = 0;
	if (buffer[index] == ' ')
		index++;
	while (buffer[index] != '*')
	{
		new_buffer[size] = buffer[index];
		index++;
		size++;
	}
	return (new_buffer);
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
			if (buffer[index + 1] == ' ' || buffer[index + 1] == '\0' \
			|| buffer[index + 1] == '\'' || buffer[index + 1] == '"')
			{
				filter = get_filter(buffer, index);
				if (get_asterisk_buffer(filter))
				{
					new_buffer[index + j - ft_strlen(filter)] = '\0';
					new_buffer = ft_strjoin(new_buffer, g_minishell.asterisk_buffer);
					j += ft_strlen(g_minishell.asterisk_buffer);
				}
			}
		}
		index++;
	}
	free(buffer);
	return (new_buffer);
}

char	*expand_vars(char *buffer)
{
	char	*new_buffer;
	int		is_in_quotes;
	int		index;

	index = 0;
	is_in_quotes = FALSE;
	new_buffer = ft_strdup(buffer);
	while (buffer[index])
	{
		if (buffer[index] == '\"')
			is_in_quotes = toogle_value(is_in_quotes);
		if (buffer[index] == '\'' && is_in_quotes == FALSE)
		{
			index++;
			while (buffer[index] != '\'' && buffer[index])
				index++;
		}

		if (buffer[index] == '$' && buffer[index + 1] \
		!= ' ' && buffer[index + 1])
			new_buffer = write_variable(new_buffer, buffer, index);
		if (buffer[index])
			index++;
	}
	new_buffer = expand_asterisk(new_buffer);
	free(buffer);
	return (new_buffer);
}
