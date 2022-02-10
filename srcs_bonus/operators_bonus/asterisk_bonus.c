#include <minishell_bonus.h>

extern t_minishell	g_minishell;

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
	char		*help;
	int			first;

	first = 1;
	path = ft_strdup("");
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp != list)
	{
		if (first == 0)
		{
			help = path;
			path = ft_strjoin(ft_strdup("/"), path);
			free(help);
		}
		help = path;
		path = ft_strjoin(ft_strdup(tmp->buffer), path);
		free(help);
		tmp = tmp->previous;
		first = 0;
	}
	return (path);
}

void	new_directory_tree(t_folder *list, struct dirent *file, char *dir)
{
	char	*tmp;
	char	*path;

	path = make_path_next(list);
	tmp = make_path_previous(list);
	tmp = ft_strjoin(tmp, file->d_name);
	if (list->next)
	{
		tmp = ft_strjoin(tmp, "/");
		tmp = ft_strjoin(tmp, path);
	}
	get_asterisk_buffer(tmp, ft_strdup(dir));
	free(tmp);
	free(path);
}

void	search_directories(t_folder *list, char *dir)
{
	DIR				*directory;
	struct dirent	*file;

	directory = create_directory(list, dir);
	file = readdir(directory);
	while (file)
	{
		if (compare(file->d_name, list->buffer) && (file->d_type == 4 || \
		file->d_type == 10) && file->d_name[0] != '.')
			new_directory_tree(list, file, dir);
		file = readdir(directory);
	}
	closedir(directory);
}

void	search_filter(t_folder *list, char *dir)
{
	struct dirent	*file;
	DIR				*directory;

	directory = create_directory(list, dir);
	if (!directory)
		return ;
	file = readdir(directory);
	while (file)
	{
		if (compare(file->d_name, list->buffer) && file->d_name[0] != '.'\
			&& (file->d_type == 10 || file->d_type == 4 || \
			g_minishell.only_dir == FALSE))
			add_result(list, file);
		file = readdir(directory);
	}
	closedir(directory);
}
