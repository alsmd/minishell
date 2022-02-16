/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:49:30 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:49:31 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	pwd(void)
{
	char	buffer[500];

	printf("%s\n", getcwd(buffer, 500));
	g_minishell.exit_code = 0;
}
