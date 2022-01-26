#include <minishell.h>

int	handle_pipe(t_node *node)
{
	int			fd[2];
	int			status;

	if (pipe(fd) == -1)
		return (1);
	add_fd(fd[0]);
	add_fd(fd[1]);
	node->output = fd[1];
	node->next->input = fd[0];
	return (0);
}
