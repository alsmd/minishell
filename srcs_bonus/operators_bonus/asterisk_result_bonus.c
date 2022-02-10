#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	add_result(t_folder *list, struct dirent *file)
{
	char	*tmp;

	tmp = ft_strjoin(make_path_previous(list), file->d_name);
	g_minishell.asterisk_buffer = ft_strjoin
		(g_minishell.asterisk_buffer, tmp);
	free(tmp);
	if (g_minishell.only_dir)
		g_minishell.asterisk_buffer = \
		ft_strjoin(g_minishell.asterisk_buffer, "/");
	g_minishell.asterisk_buffer = ft_strjoin
		(g_minishell.asterisk_buffer, " ");
	g_minishell.asterisk_found += 1;
}