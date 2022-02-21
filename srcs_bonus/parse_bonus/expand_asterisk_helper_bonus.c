/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_asterisk_helper_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:52:32 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

int	get_filter_size(char *buffer)
{
	int	index;

	index = 0;
	while (buffer[index] && buffer[index] != ' ')
		index++;
	return (index);
}

char	*get_filter(char *buffer, int index)
{
	char	*new_buffer;
	int		size;

	size = 0;
	while (buffer[index] != ' ' && index)
		index--;
	size = get_filter_size(&buffer[index]);
	new_buffer = (char *) ft_calloc(size + 1, sizeof(char));
	size = 0;
	if (buffer[index] == ' ')
		index++;
	while (buffer[index] && buffer[index] != ' ')
	{
		new_buffer[size] = buffer[index];
		index++;
		size++;
	}
	return (new_buffer);
}
