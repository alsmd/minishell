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
	g_minishell.paths = ft_split(path, ':');
}
