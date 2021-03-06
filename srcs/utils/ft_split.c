/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:47:09 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	get_size(char *s, char c)
{
	size_t		size;
	short int	str_found;

	str_found = 0;
	size = 0;
	if (!s[0])
		return (0);
	while (1)
	{
		if ((*s == c || *s == '\0') && str_found)
		{
			size++;
			str_found = 0;
		}
		else if (*s != c)
			str_found = 1;
		if (*s == '\0')
			break ;
		s++;
	}
	return (size);
}

static size_t	get_length(char *s, char c)
{
	size_t		index;

	index = 0;
	while (*s && *s != c)
	{
		index++;
		s++;
	}
	return (index);
}

static void	malloc_error(char **array, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		if (array[index])
			free(array[index]);
		index++;
	}
	free(array);
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	size_t	index;
	char	**array;

	index = 0;
	if (!s)
		return (0);
	size = get_size((char *)s, c);
	array = (char **) ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return (0);
	while (size--)
	{
		while (*s == c)
			s++;
		array[index] = ft_substr((char *)s, 0, get_length((char *)s, c));
		if (!array[index])
		{
			malloc_error(array, index);
			return (0);
		}
		s += get_length((char *)s, c);
		index++;
	}
	return (array);
}
