#include <minishell.h>

int	is_empty(char *buffer)
{
	while (*buffer)
	{
		if (!is_space(*buffer))
			return (0);
		buffer++;
	}
	return (1);
}
