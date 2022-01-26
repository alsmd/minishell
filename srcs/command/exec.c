#include <minishell.h>

extern t_minishell	g_minishell;

void	execute_cmd(t_node *cmd)
{
	if (is_builtin(cmd))
	{
		exec_builtin(cmd);
		exit(0);
	}
	if (cmd->not_exist == 1)
		exit(1);
	execve(cmd->argv[0], cmd->argv, get_matrix());
}

void	last_child(t_node *node)
{
	execute_cmd(node);
	exit(0);
}

void	parent(t_node *cmd, int fd[2])
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	execute_cmd(cmd);
	exit(0);
}
