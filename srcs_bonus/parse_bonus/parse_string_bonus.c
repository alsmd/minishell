#include <minishell_bonus.h>

extern t_minishell	g_minishell;

int	string_forward(char *string, char c, int *i)
{
	int	index;

	index = 1;
	*i += 1;
	while (string[index] != c && string[index])
		index++;
	if (string[index] == c)
		*i += 1;
	return (index);
}

int	check_quotes(char *s)
{
	int	i;
	int	quote_s;
	int	quote_d;

	i = 0;
	quote_s = 0;
	quote_d = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			i += string_forward(&s[i], '\'', &quote_s);
		if (s[i] == '\"')
			i += string_forward(&s[i], '\"', &quote_d);
		if (s[i])
			i++;
	}
	if (quote_s % 2 != 0)
		show_error(M_ERROR_SINTAX, "'''", E_ERROR_SINTAX, 0);
	if (quote_d % 2 != 0)
		show_error(M_ERROR_SINTAX, "'\"'", E_ERROR_SINTAX, 0);
	if (quote_d % 2 != 0 || quote_s % 2 != 0)
		return (1);
	return (0);
}

int	check_parentheses(char *buffer)
{
	int		index;
	int		parentheses_is_on;

	index = 0;
	parentheses_is_on = 0;

	return (0);
}

int	parse_string(char *buffer)
{
	char	quoute_is_on;
	int		parentheses_is_on;

	quoute_is_on = 0;
	parentheses_is_on = 0;
	if (check_quotes(buffer) || check_parentheses(buffer))
		return (1);
	while (*buffer)
	{
		toggle_quoute(buffer, &quoute_is_on);
		if (*buffer == '(' && quoute_is_on == FALSE)
			parentheses_is_on += 1;
		else if (*buffer == ')' && quoute_is_on == FALSE)
			parentheses_is_on -= 1;
		if (!ft_strncmp(buffer, ">>>", 3) && !quoute_is_on)
			show_error(M_ERROR_SINTAX, "'>'", E_ERROR_SINTAX, 0);
		if (*buffer == '\\' && !quoute_is_on)
			show_error(M_ERROR_SINTAX, "'\\'", E_ERROR_SINTAX, 0);
		if (*buffer == ';' && !quoute_is_on)
			show_error(M_ERROR_SINTAX, "';'", E_ERROR_SINTAX, 0);
		if ((!ft_strncmp(buffer, ">>>", 3) && !quoute_is_on) || \
			(*buffer == '\\' && !quoute_is_on) || \
			(*buffer == ';' && !quoute_is_on))
			return (1);
		buffer++;
	}
	if (parentheses_is_on != 0)
	{
		if (parentheses_is_on > 0)
			show_error(M_ERROR_SINTAX, "'('", E_ERROR_SINTAX, 0);
		else
			show_error(M_ERROR_SINTAX, "')'", E_ERROR_SINTAX, 0);
		return (1);
	}
	return (0);
}

char	*swap_chars(char *cmd, char to_find, char to_put)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			i++;
			while (cmd[i] != '\'' && cmd[i] != '\"' && cmd[i])
			{
				if (cmd[i] == to_find)
					cmd[i] = to_put;
				i++;
			}
		}
		i++;
	}
	return (cmd);
}

char	**search_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		matrix[i] = swap_chars(matrix[i], 1, ' ');
		i++;
	}
	return (matrix);
}
