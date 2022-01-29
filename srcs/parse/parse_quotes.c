#include <minishell.h>

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

int	is_quoute(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	check_quoute(char c, int *is_active, char *quoute)
{
	if (!*is_active && is_quoute(c) && c != *quoute)
	{
		*quoute = c;
		*is_active = TRUE;
		return (0);
	}
	if (*is_active == TRUE && c == *quoute)
	{
		*quoute = 0;
		*is_active = FALSE;
		return (0);
	}
	return (1);
}

char	*copy_string_trim(char **matrix, int j, int *is_active, char *quoute)
{
	int		i;
	int		desloc;
	char	*tmp;

	tmp = (char *) ft_calloc(ft_strlen(matrix[j]) + 1, sizeof(char));
	i = 0;
	desloc = 0;
	while (matrix[j][i + desloc])
	{
		if (check_quoute(matrix[j][i + desloc], is_active, quoute))
		{
			tmp[i] = matrix[j][i + desloc];
			i++;
		}
		else
			desloc++;
	}
	return (tmp);
}

void	trim_quotes(char **matrix)
{
	char	*tmp;
	int		j;
	int		is_active;
	char	quoute;

	j = 0;
	quoute = 0;
	is_active = FALSE;
	while (matrix[j])
	{
		tmp = copy_string_trim(matrix, j, &is_active, &quoute);
		free(matrix[j]);
		matrix[j] = tmp;
		j++;
	}
}
