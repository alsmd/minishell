#include <minishell.h>

void	search_command(t_node *cmd, int fd)
{
	t_node	*temp;

	temp = cmd;
	while (temp && !is_command(temp))
		temp = temp->next;
	if (temp && is_command(temp))
	{
		temp->output = fd;
		temp->output_file = 1;
	}
}

int	handle_output(t_node *cmd)
{
	int		fd;
	t_node	*tmp;

	if (cmd->relation && !ft_strncmp(cmd->relation, ">>", 2))
		fd = open(cmd->next->full_instruction, \
		O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		fd = open(cmd->next->full_instruction, \
		O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (ERROR_OPEN_FILE);
	add_fd(fd);
	tmp = cmd;
	while (cmd && !is_command(cmd))
		cmd = cmd->previous;
	if (cmd == 0)
		search_command(tmp, fd);
	else
	{
		cmd->output = fd;
		cmd->output_file = 1;
	}
	return (0);
}

int	handle_input(t_node *cmd)
{
	int		fd;
	t_node	*temp;

	temp = cmd;
	fd = open(cmd->next->full_instruction, O_RDONLY, 0777);
	if (fd == -1)
	{
		cmd->invalid_file = cmd->next->full_instruction;
		return (ERROR_OPEN_FILE);
	}
	add_fd(fd);
	while (cmd && !is_command(cmd))
		cmd = cmd->previous;
	if (cmd == 0)
	{
		while (temp && !is_command(temp))
			temp = temp->next;
		if (temp && is_command(temp))
			temp->input = fd;
	}
	else
		cmd->input = fd;
	return (0);
}

void	handle_here_doc(t_node *node)
{
	char	*delimiter;
	int		fd[2];
	char	*line;

	delimiter = ft_strjoin(ft_strdup(node->next->full_instruction), "\n");
	line = get_next_line(STDIN_FILENO);
	pipe(fd);
	while (line && ft_strncmp(line, delimiter, -1))
	{
		write_and_free(fd[1], line);
		line = get_next_line(STDIN_FILENO);
	}
	free_here_doc(line, delimiter);
	close(fd[1]);
	change_cmd_stdin(fd[0], node);
}
