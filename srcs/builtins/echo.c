#include <minishell.h>

void	my_echo(char **argv)
{
	int	broke_line;
	int	i;

	i = 1;
	broke_line = 0;
	if (!ft_strncmp(argv[1], "-n", -1))
		broke_line = 1;
	while (argv[1])
	{
		printf("%s", argv[i]);
		i++;
	}
	if (broke_line == 1)
		write (1, "\n", 1);
}
