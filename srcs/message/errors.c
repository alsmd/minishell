/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:46:09 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:46:10 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell	g_minishell;

void	show_error(char *name, char *message, int status, int has_to_exit)
{
	write(2, "Minishell: ", 12);
	write(2, name, ft_strlen(name));
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	g_minishell.exit_code = status;
	if (has_to_exit)
	{
		clean_trash();
		exit(g_minishell.exit_code);
	}
}
