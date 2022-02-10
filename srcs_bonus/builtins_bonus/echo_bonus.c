#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	my_echo(char **argv)
{
	int	broke_line;
	int	i;

	i = 1;
	broke_line = 0;
	if (argv[1] && !ft_strncmp(argv[1], "-n", -1))
	{
		broke_line = 1;
		i = 2;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (broke_line == 0)
		write (1, "\n", 1);
	g_minishell.exit_code = 0;
}
