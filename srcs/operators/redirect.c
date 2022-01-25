#include <minishell.h>

int	handle_output(t_node *cmd)
{
	int	fd;
	int	id;

	if (!ft_strncmp(cmd->previous->relation, ">>", 2))
		fd = open(cmd->full_instruction, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		fd = open(cmd->full_instruction, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (ERROR_OPEN_FILE);
	if (cmd->relation && !ft_strncmp(cmd->relation, ">", 1))
	{
		close(fd);
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	return (0);
}

int	handle_input(t_node *cmd)
{
	int	fd;
	int	id;

	fd = open(cmd->full_instruction, O_RDONLY, 0777);
	if (fd == -1)
		return (ERROR_OPEN_FILE);
	if (cmd->relation && !ft_strncmp(cmd->relation, "<", 1))
	{
		close(fd);
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	return (0);
}
