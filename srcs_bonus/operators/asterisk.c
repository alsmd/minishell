#include <minishell_bonus.h>

extern t_minishell g_minishell;

char	*make_path_previous(t_folder *list)
{
	t_folder	*tmp;
	char		*path;

	path = ft_strdup("");
	tmp = list;
	while (tmp->previous)
		tmp = tmp->previous;
	while (tmp != list)
	{
		path = ft_strjoin(path, tmp->buffer);
		path = ft_strjoin(path, "/");
		tmp = tmp->next;
	}
	return (path);
}

char	*make_path_next(t_folder *list)
{
	t_folder	*tmp;
	char		*path;
	int			first;

	first = 1;
	path = ft_strdup("");
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp != list)
	{
		if (first == 0)
			path = ft_strjoin(ft_strdup("/"), path);
		path = ft_strjoin(ft_strdup(tmp->buffer), path);
		tmp = tmp->previous;
		first = 0;
	}
	return (path);
}

void	search_directories(t_folder *list, char *dir)
{
	char			*tmp;
	struct dirent	*file;
	DIR				*directory;

	directory = opendir(ft_strjoin(ft_strdup(dir), make_path_previous(list)));
	file = readdir(directory);
	while (file)
	{
		if (compare(file->d_name, list->buffer) && file->d_type == 4 && file->d_name[0] != '.')
		{
			tmp = make_path_previous(list);
			tmp = ft_strjoin(tmp, file->d_name);
			if (list->next)
			{
				tmp = ft_strjoin(tmp, "/");
				tmp = ft_strjoin(tmp, make_path_next(list));

			}
			get_asterisk_buffer(tmp, dir);
		}
		file = readdir(directory);
	}
}

void	search_filter(t_folder *list, char *dir)
{
	char			*tmp;
	struct dirent	*file;
	DIR				*directory;

	tmp = make_path_previous(list);
	directory = opendir(ft_strjoin(ft_strdup(dir), tmp));
	file = readdir(directory);
	while (file)
	{
		if (compare(file->d_name, list->buffer) && file->d_name[0] != '.')
		{
			g_minishell.asterisk_buffer = ft_strjoin(g_minishell.asterisk_buffer, ft_strjoin(make_path_previous(list), file->d_name));
			g_minishell.asterisk_found += 1;
		}
		file = readdir(directory);
		if (file && compare(file->d_name, list->buffer) && \
		file->d_name[0] != '.' && g_minishell.asterisk_found != 0)
			g_minishell.asterisk_buffer = ft_strjoin(g_minishell.asterisk_buffer, " ");
	}
}

int	get_asterisk_buffer(char *buffer, char *dir)
{
	t_folder		*list;
	char			*tmp;
	struct dirent	*file;
	DIR				*directory;

	dir = ft_strjoin(ft_strdup(dir), "/");
	list = 0;
	list = create_folder_list(ft_strdup(buffer));
	while (list)
	{
		if (has(list->buffer, '*') && list->next)
		{
			search_directories(list, dir);
			break;
		}
		else if (list->next == 0)
			search_filter(list, dir);
		list = list->next;
	}
}
