/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_result_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:52:07 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:52:08 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	add_result(t_folder *list, struct dirent *file)
{
	char	*tmp;

	tmp = ft_strjoin(make_path_previous(list), file->d_name);
	g_minishell.asterisk_buffer = ft_strjoin
		(g_minishell.asterisk_buffer, tmp);
	free(tmp);
	if (g_minishell.only_dir)
		g_minishell.asterisk_buffer = \
		ft_strjoin(g_minishell.asterisk_buffer, "/");
	g_minishell.asterisk_buffer = ft_strjoin
		(g_minishell.asterisk_buffer, " ");
	g_minishell.asterisk_found += 1;
}
