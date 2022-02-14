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

int		check_parentheses(char *str, int i, char quoute_is_on, int *pare_is_on)
{
	if(str[i] == '(' && quoute_is_on == FALSE)
	{
		if (!found_operator_left(str, i - 1)  || found_operator_right(str, i + 1))
		{
			show_error(M_ERROR_SINTAX, "'('", E_ERROR_SINTAX, 0);
			return (1);
		}
		*pare_is_on += 1;
	}
	else if (str[i] == ')' && quoute_is_on == FALSE)
	{
		if (!found_operator_right(str, i) || found_operator_left(str, i - 1) || another_parenthesis(str, i + 1) \
			|| *pare_is_on == 0)
		{
			show_error(M_ERROR_SINTAX, "')'", E_ERROR_SINTAX, 0);
			return (1);
		}
		*pare_is_on -= 1;
	}
	return (0);
}

int	wrong_format(char *buffer, int index, char *quoute, int *par_is_on)
{
	toggle_quoute(&buffer[index], quoute);
	if (check_parentheses(buffer, index, *quoute, par_is_on))
		return (1);
	if (!ft_strncmp(&buffer[index], ">>>", 3) && !*quoute)
		show_error(M_ERROR_SINTAX, "'>'", E_ERROR_SINTAX, 0);
	if (buffer[index] == '\\' && !*quoute)
		show_error(M_ERROR_SINTAX, "'\\'", E_ERROR_SINTAX, 0);
	if (buffer[index] == ';' && !*quoute)
		show_error(M_ERROR_SINTAX, "';'", E_ERROR_SINTAX, 0);
	if ((!ft_strncmp(&buffer[index], ">>>", 3) && !*quoute) || \
		(buffer[index] == '\\' && !*quoute) || \
		(buffer[index] == ';' && !*quoute))
		return (1);
	return (0);
}

int	parse_string(char *buffer)
{
	char	quoute_is_on;
	int		parentheses_is_on;
	int		index;

	quoute_is_on = 0;
	parentheses_is_on = 0;
	index = 0;
	if (check_quotes(buffer))
		return (1);
	while (buffer[index])
	{
		if (wrong_format(buffer, index, &quoute_is_on, &parentheses_is_on))
			return (1);
		index++;
	}
	if (parentheses_is_on  > 0)
		show_error(M_ERROR_SINTAX, "'('", E_ERROR_SINTAX, 0);
	else if (parentheses_is_on < 0)
		show_error(M_ERROR_SINTAX, "')'", E_ERROR_SINTAX, 0);
	return (parentheses_is_on);
}
