/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:46:38 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:46:39 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell	g_minishell;

void	get_path(void)
{
	t_env	*init;
	char	*path;

	init = g_minishell.env;
	path = 0;
	while (init)
	{
		if (!ft_strncmp(init->key, "PATH", -1))
			path = init->value;
		init = init->next;
	}
	if (g_minishell.paths)
		free_matrix(g_minishell.paths);
	g_minishell.paths = ft_split(path, ':');
}
