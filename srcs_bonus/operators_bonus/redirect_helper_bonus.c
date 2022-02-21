/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_helper_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:52:17 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	change_cmd_stdin(int fd, t_node *node)
{
	t_node	*temp;

	temp = node;
	while (node && !is_command(node))
		node = node->previous;
	if (node == 0)
	{
		while (temp && !is_command(temp))
			temp = temp->next;
		temp->input = fd;
	}
	else
		node->input = fd;
}

void	write_and_free(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	free(line);
}

void	free_here_doc(char *line, char *delimiter)
{
	if (line)
		free(line);
	if (delimiter)
		free(delimiter);
}
