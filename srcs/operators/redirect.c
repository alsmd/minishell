#include <minishell.h>

int	handle_output(t_node *cmd)
{
	int	fd;
	int	id;
	t_node *temp;

	temp = cmd;
	if (!ft_strncmp(cmd->relation, ">>", 2))
		fd = open(cmd->next->full_instruction, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		fd = open(cmd->next->full_instruction, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (ERROR_OPEN_FILE);
	add_fd(fd);
	while (cmd && !is_command(cmd))
		cmd = cmd->previous;
	if (cmd == 0)
	{
		while(temp && !is_command(temp))
			temp = temp->next;
		temp->output = fd;
	}
	else
		cmd->output = fd;
	return (0);
}

int	handle_input(t_node *cmd)
{
	int	fd;
	int	id;
	t_node *temp;

	temp = cmd;
	fd = open(cmd->next->full_instruction, O_RDONLY, 0777);
	if (fd == -1)
		return (ERROR_OPEN_FILE);
	add_fd(fd);
	while (cmd && !is_command(cmd))
		cmd = cmd->previous;
	if (cmd == 0)
	{
		while(temp && !is_command(temp))
			temp = temp->next;
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
	t_node *temp;

	temp = node;
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
	if (node == 0)
	{
		while(temp && !is_command(temp))
			temp = temp->next;
		temp->input = fd[0];


	}
	else
	{
		
		printf("\n|%s|\n%s\n", node->full_instruction, node->relation);
		node->input = fd[0];
	}
}
