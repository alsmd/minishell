#include <minishell.h>

extern t_minishell g_minishell;

int	get_variable_len(char *key)
{
	int i;
	i = 0;
	while (key[i] && key[i] != ' ' && key[i] != '\'' && key[i] != '\"')
		i++;
	return (i);
}


int toogle_value(int signal)
{
	if (signal == 0)
		return (TRUE);
	return (FALSE);
}

char *expand_var(char *key)
{
	t_env *init;

	init = g_minishell.env;
	while (init)
	{
		if (!ft_strncmp(init->key, key, get_variable_len(key)))
		{
			return (init->value);
		}
		init = init->next;
	}
	return (ft_calloc(1,1));
}


void cut_char(char *buffer)
{
	int index;
	int is_in_quotes;
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



char *check_expand(char *buffer)
{
	char *new_buffer;
	int is_in_quotes;
	int index;

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
		if (buffer[index] == '$')
		{
			//limitando o tamanho para o join, colocando byte nulo ante do $
			cut_char(new_buffer);			
			//cat "$USER" | echo '$PATH' | grep "''$USER''"
			// printf("%c\n", new_buffer[index]);
			new_buffer = ft_strjoin(new_buffer, expand_var(&buffer[index + 1]));
			new_buffer = ft_strjoin(new_buffer, &buffer[index + get_variable_len(&buffer[index])]);
		}
		index++;
	}
	return (new_buffer);
}