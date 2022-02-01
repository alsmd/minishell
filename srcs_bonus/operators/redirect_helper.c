#include <minishell.h>

extern t_minishell	g_minishell;

void	change_cmd_stdin(int fd, t_node *node)
{
	t_node	*temp;

	temp = node;
	while (node && !is_command(node))
		node = node->previous;
	if (node == 0)
	{
		while (temp && !is_command(temp))
			temp = temp->next;
		temp->input = fd;
	}
	else
		node->input = fd;
}

void	write_and_free(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	free(line);
}

void	free_here_doc(char *line, char *delimiter)
{
	if (line)
		free(line);
	if (delimiter)
		free(delimiter);
}
