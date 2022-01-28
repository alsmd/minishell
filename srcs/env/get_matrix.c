#include <minishell.h>

extern t_minishell	g_minishell;

int	get_env_len(void)
{
	int		len;
	t_env	*init;

	init = g_minishell.env;
	len = 0;
	while (init)
	{
		init = init->next;
		len++;
	}
	return (len);
}

char	**get_matrix(void)
{
	int		len;
	t_env	*init;
	char	**my_env;
	int		index;

	index = 0;
	init = g_minishell.env;
	len = get_env_len();
	my_env = (char **)ft_calloc(sizeof(char *), len + 1);
	while (init)
	{
		my_env[index] = ft_strdup(init->key);
		my_env[index] = ft_strjoin(my_env[index], "=");
		my_env[index] = ft_strjoin(my_env[index], init->value);
		index++;
		init = init->next;
	}
	return (my_env);
}

char	*get_var_value(char *key)
{
	t_env	*init;
	

	init = g_minishell.env;
	if (!ft_strncmp(key, "?",  get_variable_len(key)))
		return (ft_itoa(g_minishell.exit_code));
	while (init)
	{
		if (!ft_strncmp(init->key, key, get_variable_len(key)))
			return (ft_strdup(init->value));
		init = init->next;
	}
	return (ft_calloc(1, 1));
}
