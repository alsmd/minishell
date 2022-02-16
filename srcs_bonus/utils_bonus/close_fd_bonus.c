/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:52:56 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:52:57 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	close_fd(int fd)
{
	t_fd	*fds;

	if (fd == STDIN_FILENO || fd == STDOUT_FILENO)
		return ;
	fds = g_minishell.fds;
	while (fds)
	{
		if (fds->value == fd)
			close(fds->value);
		fds = fds->next;
	}
}
