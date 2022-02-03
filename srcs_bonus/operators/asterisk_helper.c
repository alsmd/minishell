#include <minishell_bonus.h>

extern t_minishell g_minishell;

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