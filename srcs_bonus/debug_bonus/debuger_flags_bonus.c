#include <minishell_bonus.h>

extern t_minishell	g_minishell;

int	delete_flags(char *flag)
{
	if (!ft_strncmp(flag, "--hide-node", -1))
	{
		g_minishell.debug_flags.show_nodes = FALSE;
		return (1);
	}
	else if (!ft_strncmp(flag, "--hide-subshell", -1))
	{
		g_minishell.debug_flags.show_subshell = FALSE;
		return (1);
	}
	else if (!ft_strncmp(flag, "--stop-cmd", -1))
	{
		g_minishell.debug_flags.exec_cmd = FALSE;
		return (1);
	}
	return (0);
}

void	turn_on_debug_flags(char **flags)
{
	int	i;

	i = 0;
	while (flags[++i])
	{
		if (!ft_strncmp(flags[i], "--show-node", -1))
			g_minishell.debug_flags.show_nodes = TRUE;
		else if (!ft_strncmp(flags[i], "--show-subshell", -1))
			g_minishell.debug_flags.show_subshell = TRUE;
		else if (!ft_strncmp(flags[i], "--exec-cmd", -1))
			g_minishell.debug_flags.exec_cmd = TRUE;
		else if (delete_flags(flags[i]))

			continue ;
		else if (!ft_strncmp(flags[i], "-h", -1) && i == 1 && !flags[i + 1])
			print_flags();
		else
			printf("invalid flag: use -h to see the valids!");
	}
}

void	print_flags(void)
{
	printf("use %s--show-node%s to show node relations\n", GREEN_LIGHT, RESET);
	printf("use %s--show-subshell %sto show subshell process\n", \
	GREEN_LIGHT, RESET);
	printf("use %s--exec-cmd %sto execute command line\n", GREEN_LIGHT, RESET);
	printf("use %s--hide-node %sto hide node relarions\n", YELLOW_LIGHT, RESET);
	printf("use %s--hide-subshell %sto hide subshell process\n", \
	YELLOW_LIGHT, RESET);
	printf("use %s--stop-cmd %sto stop execution of command line\n", \
	YELLOW_LIGHT, RESET);
}
