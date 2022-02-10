#include <minishell_bonus.h>

extern t_minishell	g_minishell;

int	found_operator(char *buffer, int index, int direction)
{
	while (index > 0 && buffer[index])
	{
		if (is_in(g_minishell.operators, &(buffer[index])))
			return (1);
		if (buffer[index] != ' ')
			return (0);
		index += direction;
	}
	return (0);
}

int	another_parenthesis(char *buffer, int index)
{
	while (buffer[index])
	{
		if (buffer[index] == '(')
			return (1);
		if (buffer[index] != ' ')
			return (0);
		index += 1;
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
