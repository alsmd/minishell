/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:45:01 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:45:02 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell	g_minishell;

void	env(void)
{
	t_env	*init;

	init = g_minishell.env;
	while (init)
	{
		printf("%s=%s\n", init->key, init->value);
		init = init->next;
	}
	g_minishell.exit_code = 0;
}

void	export(char *command)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (command[i] && command[i] != '=')
		i++;
	key = ft_substr(command, 0, i);
	value = ft_substr(command, i + 1, ft_strlen(command) - i + 1);
	unset(key);
	add_variable(key, value);
	g_minishell.exit_code = 0;
}

void	free_env_node(t_env *to_clean)
{
	free(to_clean->key);
	free(to_clean->value);
	free(to_clean);
}

void	unset(char *key)
{
	t_env	*init;
	t_env	*previous;

	previous = 0;
	init = g_minishell.env;
	while (init)
	{
		if (!ft_strncmp(init->key, key, -1))
		{
			if (previous == 0)
				g_minishell.env = init->next;
			else
			{
				previous->next = init->next;
				if (init->next)
					init->next->previous = previous;
			}
			free_env_node(init);
			break ;
		}
		previous = init;
		init = init->next;
	}
	g_minishell.exit_code = 0;
}
