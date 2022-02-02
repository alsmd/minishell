#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == 0)
		return ;
	while (matrix[i])
	{
		if (matrix[i])
			free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	clean_node(void)
{
	t_node	*temp;

	if (g_minishell.node)
	{
		while (g_minishell.node)
		{
			temp = g_minishell.node;
			g_minishell.node = g_minishell.node->next;
			if (temp->argv)
				free_matrix(temp->argv);
			free(temp->full_instruction);
			if (temp->full_path)
				free(temp->full_path);
			free(temp);
		}
	}
}

void	clean_env(void)
{
	t_env	*temp;

	while (g_minishell.env)
	{
		temp = g_minishell.env;
		g_minishell.env = g_minishell.env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	clean_fd(void)
{
	t_fd	*temp;

	while (g_minishell.fds)
	{
		temp = g_minishell.fds;
		g_minishell.fds = g_minishell.fds->next;
		free(temp);
	}
}

void	clean_trash(void)
{
	clean_node();
	clean_env();
	if (g_minishell.operators[7] == NULL)
		free(g_minishell.operators[8]);
	free_matrix(g_minishell.operators);
	clean_fd();
	free_matrix(g_minishell.paths);
}
