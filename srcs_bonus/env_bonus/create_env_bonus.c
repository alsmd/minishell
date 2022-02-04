#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	add_variable(char *key, char *value)
{
	t_env	*new_variable;
	t_env	*init;

	init = g_minishell.env;
	new_variable = (t_env *)ft_calloc(sizeof(t_env), 1);
	new_variable->key = key;
	new_variable->value = value;
	if (init == 0)
		g_minishell.env = new_variable;
	else
	{
		while (init->next)
			init = init->next;
		new_variable->previous = init;
		init->next = new_variable;
	}
}

void	create_env(char **envp)
{
	char	*key;
	char	*value;
	int		line;
	int		len;

	line = 0;
	len = 0;
	while (envp[line])
	{
		while (envp[line][len] != '=' && envp[line][len])
			len++;
		key = ft_substr(envp[line], 0, len);
		value = ft_substr(envp[line], len + 1, ft_strlen(envp[line]) - len + 1);
		add_variable(key, value);
		len = 0;
		line++;
	}
}
