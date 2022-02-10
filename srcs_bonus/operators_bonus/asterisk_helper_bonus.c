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

void	get_asterisk_buffer(char *buffer, char *dir)
{
	t_folder		*list;
	t_folder		*begin;

	if (buffer[0] == '/')
	{
		free(dir);
		dir = ft_strdup("");
	}
	if (buffer[ft_strlen(buffer) - 1] == '/')
		g_minishell.only_dir = TRUE;
	list = 0;
	list = create_folder_list(ft_strdup(buffer));
	begin = list;
	while (list)
	{
		if (has(list->buffer, '*') && list->next)
		{
			search_directories(list, dir);
			break ;
		}
		else if (list->next == 0)
			search_filter(list, dir);
		list = list->next;
	}
	free_list(begin);
	free(dir);
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
