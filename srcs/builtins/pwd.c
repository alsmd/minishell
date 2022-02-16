/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:45:13 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:45:14 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell	g_minishell;

void	pwd(void)
{
	char	buffer[500];

	printf("%s\n", getcwd(buffer, 500));
	g_minishell.exit_code = 0;
}
