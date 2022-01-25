#include <minishell.h>

extern t_minishell g_minishell;

t_env	*add_variable(char *key, char *value, t_env *previous)
{
	t_env *new_variable;

	new_variable = (t_env *)ft_calloc(sizeof(t_env), 1);
	new_variable->key= key;
	new_variable->value = value;
	new_variable->previous = previous;
	return (new_variable);
}


void	create_env(char **env)
{
	char *key;
	char *value;
	int line;
	int len;
	t_env *init;

	init = (t_env *)ft_calloc(sizeof(t_env), 1);
	g_minishell.env = init;
	line = 0;
	len = 0;
	while (env[line])
	{
		while (env[line][len] != '=' && env[line][len])
			len++;
		key = ft_substr(env[line], 0, len);	
		value = ft_substr(env[line], len + 1, ft_strlen(env[line]) - len + 1);
		init->next = add_variable(key, value, init);
		init = init->next;
		len = 0;
		line++;
	}
		
}