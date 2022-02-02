#include <minishell_bonus.h>

extern t_minishell	g_minishell;

t_node	*parse_cmd(char *command)
{
	t_node	*new_cmd;

	new_cmd = (t_node *) ft_calloc(1, sizeof(t_node));
	new_cmd->full_instruction = ft_strtrim(command, " ");
	new_cmd->full_instruction = swap_chars(new_cmd->full_instruction, ' ', 1);
	new_cmd->argv = ft_split(new_cmd->full_instruction, ' ');
	if (new_cmd->argv && new_cmd->argv[0])
		new_cmd->full_path = ft_strdup(new_cmd->argv[0]);
	else
		new_cmd->full_path = ft_strdup("");
	new_cmd->argv = search_matrix(new_cmd->argv);
	return (new_cmd);
}

t_node	*add_new_cmd(char *command, char *relation)
{
	t_node	*begin;
	t_node	*new_cmd;

	new_cmd = parse_cmd(command);
	if (is_builtin(new_cmd))
		new_cmd->is_builtin = 1;
	else if (is_absolute_path(new_cmd->argv[0]))
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
	if (!cmd)
		return (FALSE);
	if (!ft_strncmp(cmd, "/", 1))
		return (TRUE);
	else if (!ft_strncmp(cmd, "./", 2))
		return (TRUE);
	else if (!ft_strncmp(cmd, "../", 3))
		return (TRUE);
	return (FALSE);
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
