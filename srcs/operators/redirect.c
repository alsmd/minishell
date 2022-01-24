/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:44:26 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/24 20:35:44 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	output(t_node *cmd)
{
	int	fd;
	int	id;

	if (!ft_strncmp(cmd->previous->relation, ">>", 2))
		fd = open(cmd->full_instruction, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		fd = open(cmd->full_instruction, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (ERROR_OPEN_FILE);
	dup2(fd, STDOUT_FILENO);
	return (0);
}
