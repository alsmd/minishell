/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_commands_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:50:03 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:50:04 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	parse_builtin_final(void)
{
	int	id;

	expand_node(g_minishell.node);
	trim_quotes(g_minishell.node->argv);
	if (g_minishell.debug_is_on && ft_strncmp(g_minishell.node->argv[0], \
		"debug", ft_strlen(g_minishell.node->argv[0])) && \
		g_minishell.debug_mode == 1)
	{
		id = fork();
		if (id == 0)
		{
			print_debuger_table(g_minishell.node);
			clean_trash();
			exit (0);
		}	
		waitpid(id, NULL, 0);
		if (g_minishell.debug_flags.exec_cmd == FALSE)
			return ;
	}
	if (g_minishell.debug_mode == 0)
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
		signals(IGNORE);
		if (id == 0)
		{
			if (g_minishell.debug_mode == 0)
				link_relations();
			exec_commands(0);
		}
		waitpid(id, &g_minishell.exit_code, 0);
		g_minishell.exit_code = get_status(g_minishell.exit_code);
	}
}
