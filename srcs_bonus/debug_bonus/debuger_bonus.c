#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	debug_mode(char *buffer)
{
	t_debug	debug_flags;

	debug_flags = g_minishell.debug_flags;
	g_minishell.debug_mode = 1;
	clean_trash();
	init_shell(g_minishell.str_env);
	g_minishell.debug_mode = 1;
	g_minishell.debug_is_on = 1;
	g_minishell.debug_flags = debug_flags;
	(void)buffer;
	make_shell_command(buffer);
	clean_trash();
	exit(0);
}

void	print_debuger_table(t_node *node)
{
	if (g_minishell.debug_flags.show_nodes)
		show_nodes(node);
	if (g_minishell.debug_flags.show_subshell && node->subshell)
		show_subshell(ft_strdup(node->subshell));
}

void	turn_on_debug_flags(char **flags)
{
	int	i;

	i = 1;
	while (flags[i])
	{
		if (!ft_strncmp(flags[i], "--show-node", -1))
			g_minishell.debug_flags.show_nodes = TRUE;
		if (!ft_strncmp(flags[i], "--show-subshell", -1))
			g_minishell.debug_flags.show_subshell = TRUE;
		if (!ft_strncmp(flags[i], "--exec-cmd", -1))
			g_minishell.debug_flags.exec_cmd = TRUE;
		i++;
	}
}


void	debuger(char **flags)
{
	if (!g_minishell.debug_is_on)
	{
		printf("Debug mode is enable!\n");
		g_minishell.debug_is_on = 1;
	}
	else if (flags && !flags[1])
	{
		printf("Debug mode is disable!\n");
		ft_bzero(&g_minishell.debug_flags, sizeof(t_debug));
		g_minishell.debug_mode = 0;
		g_minishell.debug_is_on = 0;
	}
	if (g_minishell.debug_is_on)
		turn_on_debug_flags(flags);
}
