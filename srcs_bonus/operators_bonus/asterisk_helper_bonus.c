#include <minishell_bonus.h>

extern t_minishell	g_minishell;

t_folder	*add_to_list(t_folder **begin, char *buffer)
{
	t_folder	*new_folder;
	t_folder	*tmp;

	new_folder = (t_folder *) ft_calloc(1, sizeof(t_folder));
	new_folder->buffer = buffer;
	(void)begin;
	if (*begin == 0)
		*begin = new_folder;
	else
	{
		tmp = *begin;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_folder;
		new_folder->previous = tmp;
	}
	return (new_folder);
}

t_folder	*create_folder_list(char *buffer)
{
	t_folder	*list;
	int			index;
	int			desloc;

	desloc = 0;
	index = 0;
	list = 0;
	while (buffer[index])
	{
		if (buffer[index] == '/')
		{
			buffer[index] = '\0';
			if (buffer[index + 1])
			{
				add_to_list(&list, ft_strdup(&buffer[desloc]));
				desloc = index + 1;
			}
		}
		index++;
	}
	if (buffer[desloc])
		add_to_list(&list, ft_strdup(&buffer[desloc]));
	free(buffer);
	return (list);
}

void	free_list(t_folder *begin)
{
	t_folder	*tmp;

	while (begin)
	{
		tmp = begin;
		begin = begin->next;
		free(tmp->buffer);
		free(tmp);
	}
}

void	search_filter(t_folder *list, char *dir)
{
	char			*tmp;
	struct dirent	*file;
	DIR				*directory;

	directory = create_directory(list, dir);
	if (!directory)
		return ;
	file = readdir(directory);
	while (file)
	{
		if (compare(file->d_name, list->buffer) && file->d_name[0] != '.')
		{
			tmp = ft_strjoin(make_path_previous(list), file->d_name);
			g_minishell.asterisk_buffer = ft_strjoin
				(g_minishell.asterisk_buffer, tmp);
			free(tmp);
			g_minishell.asterisk_buffer = ft_strjoin
				(g_minishell.asterisk_buffer, " ");
			g_minishell.asterisk_found += 1;
		}
		file = readdir(directory);
	}
	closedir(directory);
}

DIR	*create_directory(t_folder *list, char *dir)
{
	char			*path;
	char			*tmp;
	DIR				*directory;

	path = make_path_previous(list);
	tmp = ft_strjoin(ft_strdup(dir), path);
	directory = opendir(tmp);
	free(tmp);
	free(path);
	return (directory);
}
