/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:45:25 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell	g_minishell;

void	close_prev_fd(t_node *node)
{
	if (node->previous && is_command(node->previous))
	{
		close_fd(node->previous->input);
		close_fd(node->previous->output);
	}
}

int	get_status(int status)
{
	return (((status) & 0xff00) >> 8);
}

void	validade_command(t_node *node)
{
	if (node->not_exist == 1 && node->is_absolute_path)
		show_error(node->argv[0], M_INVALID_FILE, E_COMMAND_NOT_FOUND, 1);
	else if (node->is_absolute_path && \
	node->is_executable == 0 && node->not_exist == 0)
		show_error(node->argv[0], M_PERMISSION, E_PERMISSION, 1);
	else if (node->not_exist == 1)
		show_error(node->argv[0], M_COMMAND_NOT_FOUND, \
		E_COMMAND_NOT_FOUND, 1);
	else if (node->invalid_file)
		show_error(node->invalid_file, M_INVALID_FILE, E_COMMAND_NOT_FOUND, 1);
}
