#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	close_fd(int fd)
{
	t_fd	*fds;

	if (fd == STDIN_FILENO || fd == STDOUT_FILENO)
		return ;
	fds = g_minishell.fds;
	while (fds)
	{
		if (fds->value == fd)
			close(fds->value);
		fds = fds->next;
	}
}
