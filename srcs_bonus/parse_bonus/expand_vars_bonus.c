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
	free(buffer);
	return (new_buffer);
}