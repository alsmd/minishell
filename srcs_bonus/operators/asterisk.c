#include <minishell_bonus.h>

extern t_minishell g_minishell;

int	get_asterisk_buffer(char *buffer)
{
	int				index;
	struct dirent	*file;
	DIR				*directory;

	index = 0;
	if (g_minishell.asterisk_buffer)
		free(g_minishell.asterisk_buffer);
	g_minishell.asterisk_buffer = ft_strdup("");
	directory = opendir(get_var_value("PWD"));
	file = readdir(directory);
	while (file)
	{
		if (file->d_name[0] != '.' && (buffer[0] == '\0' || !ft_strncmp(file->d_name, buffer, ft_strlen(buffer))))
		{
			index++;
			g_minishell.asterisk_buffer = ft_strjoin(g_minishell.asterisk_buffer, file->d_name);
			g_minishell.asterisk_buffer = ft_strjoin(g_minishell.asterisk_buffer, " ");
		}
		file = readdir(directory);
	}
	closedir(directory);
	return (index);
}	