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
	char	*temp;
	int		index;

	index = 0;
	init = g_minishell.env;
	len = get_env_len();
	my_env = (char **)ft_calloc(sizeof(char *), len + 1);
	while (init)
	{
		my_env[index] = ft_strdup(init->key);
		temp = my_env[index];
		my_env[index] = ft_strjoin(my_env[index], "=");
		free(temp);
		temp = my_env[index];
		my_env[index] = ft_strjoin(my_env[index], init->value);
		free(temp);
		index++;
		init = init->next;
	}
	return (my_env);
}
