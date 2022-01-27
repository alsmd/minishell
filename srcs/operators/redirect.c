#include <minishell.h>

int	handle_output(t_node *cmd)
{
	int	fd;
	int	id;

	if (!ft_strncmp(cmd->relation, ">>", 2))
		fd = open(cmd->next->full_instruction, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		fd = open(cmd->next->full_instruction, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (ERROR_OPEN_FILE);
	add_fd(fd);
	while (cmd && !is_command(cmd))
		cmd = cmd->previous;
	cmd->output = fd;
	return (0);
}

int	handle_input(t_node *cmd)
{
	int	fd;
	int	id;

	fd = open(cmd->next->full_instruction, O_RDONLY, 0777);
	if (fd == -1)
		return (ERROR_OPEN_FILE);
	add_fd(fd);
	while (cmd && !is_command(cmd))
		cmd = cmd->previous;
	cmd->input = fd;
	return (0);
}

void	handle_here_doc(t_node *node)
{
	char	*delimiter;
	int		fd[2];
	char	*line;
	
	delimiter = ft_strjoin(node->next->full_instruction, "\n");
	line = get_next_line(STDIN_FILENO);
	pipe(fd);
	while (ft_strncmp(line, delimiter, -1))
	{
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd[1]);
	while (node && !is_command(node))
		node = node->previous;
	node->input = fd[0];
}
