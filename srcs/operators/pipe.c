/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:33:12 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/24 21:37:26 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_pipe(t_node *node)
{
	int			id;
	int			fd[2];
	int			status;

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id == -1)
		return (1);
	if (id != 0)
	{
		waitpid(id, &status, 0);
		parent(node, fd);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	return (0);
}