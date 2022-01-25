#include <minishell.h>

int	handle_pipe(t_node *node)
{
	int			id;
	int			fd[2];
	int			status;

	if (pipe(fd) == -1)
		return (1);
	id = fork();
	if (id == -1)
		return (1);
	if (id != 0)
	{
		waitpid(id, &status, 0);
		parent(node, fd);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	return (0);
}