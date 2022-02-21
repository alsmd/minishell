/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:49:12 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 12:45:22 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

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

void	show_variables(void)
{
	t_env	*init;
	char	*buffer;
	
	buffer = ft_strdup("declare -x");
	init = g_minishell.env;
	while (init)
	{
		printf("%s %s=\"%s\"\n", buffer, init->key, init->value);
		init = init->next;
	}
	free(buffer);
	g_minishell.exit_code = 0;
}

void	export(char *command)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (!command)
	{
		show_variables();
		g_minishell.exit_code = 0;
		return ;
	}
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
	if (!key)
		return ;
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
