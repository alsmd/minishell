#include <minishell.h>

extern t_minishell	g_minishell;

t_node	*add_new_cmd(char *command, char *relation)
{
	t_node	*begin;
	t_node	*new_cmd;

	new_cmd = (t_node *) ft_calloc(1, sizeof(t_node));
	new_cmd->full_instruction = ft_strtrim(command, " ");
	new_cmd->full_instruction = swap_chars(new_cmd->full_instruction, ' ', 1);
	new_cmd->argv = ft_split(new_cmd->full_instruction, ' ');
	new_cmd->argv = search_matrix(new_cmd->argv);
	new_cmd->argv = trim_quotes(new_cmd->argv);
	if (is_absolute_path(new_cmd->argv[0]))
		check_absolute_path(new_cmd);
	else
		check_command_exist(new_cmd);
	new_cmd->input = STDIN_FILENO;
	new_cmd->output = STDOUT_FILENO;
	new_cmd->relation = relation;
	begin = g_minishell.node;
	if (begin == 0)
		g_minishell.node = new_cmd;
	else
	{
		while (begin->next)
			begin = begin->next;
		new_cmd->previous = begin;
		begin->next = new_cmd;
	}
	return (new_cmd);
}

int	is_absolute_path(char *cmd)
{
	if (!ft_strncmp(cmd, "/", 1))
		return (TRUE);
	else if (!ft_strncmp(cmd, "./", 2))
		return (TRUE);
	else if (!ft_strncmp(cmd, "../", 3))
		return (TRUE);
	return (FALSE);
}

void	check_absolute_path(t_node *cmd)
{
	if (access(cmd->argv[0], F_OK) == 0)
		cmd->not_exist = 0;
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
	while (g_minishell.paths && g_minishell.paths[index] != 0)
	{
		tmp = ft_strjoin(g_minishell.paths[index], "/");
		cmd_path = ft_strjoin(tmp, cmd->argv[0]);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
		{
			free(cmd->argv[0]);
			cmd->argv[0] = cmd_path;
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
	if (node->previous == 0)
		return (1);
	if (node->previous->relation[0] == '|')
		return (1);
	if (node->relation == 0 && node->previous->relation[0] == '|')
		return (1);
	return (0);
}

void	add_fd(int fd)
{
	t_fd	*new_fd;
	t_fd	*fds;

	new_fd = (t_fd *) ft_calloc(sizeof(t_fd), 1);
	new_fd->value = fd;
	fds = g_minishell.fds;
	if (fds == 0)
		g_minishell.fds = new_fd;
	else
	{
		while (fds->next)
			fds = fds->next;
		fds->next = new_fd;
	}
}
