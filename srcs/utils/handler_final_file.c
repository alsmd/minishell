/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_final_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:47:49 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:47:50 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler_final_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != 0)
	{
		free(line);
		line = get_next_line(fd);
	}
}
