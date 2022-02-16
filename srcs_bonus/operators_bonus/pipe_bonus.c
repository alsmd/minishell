/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:52:11 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:52:12 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

int	handle_pipe(t_node *node)
{
	int			fd[2];

	if (pipe(fd) == -1)
		return (1);
	add_fd(fd[0]);
	add_fd(fd[1]);
	node->next->input = fd[0];
	while (node && !is_command(node))
		node = node->previous;
	if (node->output_file == 0)
		node->output = fd[1];
	else
		close(fd[1]);
	return (0);
}
