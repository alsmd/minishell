#include <minishell.h>

int	handle_pipe(t_node *node)
{
	int			fd[2];

	if (pipe(fd) == -1)
		return (1);
	add_fd(fd[0]);
	add_fd(fd[1]);
	node->next->input = fd[0];
	while (node && !is_command(node))
		node = node->previous;
	if (node && node->output_file == 0)
		node->output = fd[1];
	else
		close(fd[1]);
	return (0);
}
