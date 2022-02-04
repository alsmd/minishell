#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	parse_builtin_final(void)
{
	expand_node(g_minishell.node);
	trim_quotes(g_minishell.node->argv);
	exec_builtin(g_minishell.node);
}

void	make_shell_command(char *buffer)
{
	int	id;

	get_path();
	create_relations(buffer);
	free(buffer);
	if (check_grammar())
	{
		clean_node();
		return ;
	}
	if (is_builtin(g_minishell.node) == TRUE && g_minishell.node->next == 0)
		parse_builtin_final();
	else
	{
		id = fork();
		signals(3);
		if (id == 0)
		{
			link_relations();
			exec_commands(0);
		}
		waitpid(id, &g_minishell.exit_code, 0);
		g_minishell.exit_code = get_status(g_minishell.exit_code);
	}
}
