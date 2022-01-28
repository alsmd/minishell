#include <minishell.h>

extern t_minishell	g_minishell;

void	check_absolute_path(t_node *cmd)
{
	cmd->is_absolute_path = TRUE;
	if (access(cmd->argv[0], F_OK) == 0)
	{
		cmd->not_exist = 0;
		if (access(cmd->argv[0], X_OK) == 0)
			cmd->is_executable = 1;
	}
	else
		cmd->not_exist = 1;
}

void	check_command_exist(t_node *cmd)
{
	char	*cmd_path;
	char	*tmp;
	int		index;
	int		exist;

	index = 0;
	exist = 0;
	if (!cmd->argv[0])
		return ;
	while (g_minishell.paths && g_minishell.paths[index] != 0)
	{
		tmp = ft_strjoin(ft_strdup(g_minishell.paths[index]), "/");
		cmd_path = ft_strjoin(tmp, cmd->argv[0]);
		// free(tmp);
		if (access(cmd_path, F_OK) == 0)
		{
			
			cmd->full_path = cmd_path;
			exist = 1;
			break ;
		}
		else
			free(cmd_path);
		index++;
	}
	if (exist == 0)
		cmd->not_exist = 1;
}

int	is_command(t_node *node)
{
	if (node->previous == 0 && node->argv[0])
		return (1);
	if (node->previous == 0)
		return (0);
	if (node->previous->relation &&  node->previous->relation[0] == '|')
		return (1);
	if (node->previous->relation && node->previous->relation[0] == ' ')
		return (1);
	if (node->relation == 0 && node->previous->relation[0] == '|')
		return (1);
	return (0);
}
