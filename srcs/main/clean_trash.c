#include <minishell.h>

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


void clean_node(void)
{
	t_node	*temp;

		printf("full_path: %s\nok\n", g_minishell.node->full_path);
	if (g_minishell.node->full_path)
		free(g_minishell.node->full_path);
	while(g_minishell.node)
	{
		temp = g_minishell.node;
		g_minishell.node = g_minishell.node->next;
		if (temp->argv)
			free_matrix(temp->argv);
		free(temp->full_instruction);
		free(temp);
	}
}

void	clean_env(void)
{
	t_env *temp;

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
	t_fd *temp;

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
	free_matrix(g_minishell.operators);
	clean_fd();
	free_matrix(g_minishell.paths);


}