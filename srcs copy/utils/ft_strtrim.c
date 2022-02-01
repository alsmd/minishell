/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:47:58 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/28 11:27:14 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static size_t	helper_is_in(const char *array, char c)
{
	size_t	index;

	index = 0;
	while (array[index])
	{
		if (array[index] == c)
			return (1);
		index++;
	}
	return (0);
}

static size_t	get_size(char const *s, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	size;

	start = 0;
	end = ft_strlen(s);
	if (!end)
		return (0);
	end--;
	while (helper_is_in(set, s[start]) && s[start])
		start++;
	if (start == ft_strlen(s))
		return (0);
	while (helper_is_in(set, s[end]) && end)
		end--;
	size = end - start + 1;
	return (size);
}

char	*ft_strtrim(char *s1, char const *set)
{
	char	*string;
	size_t	size;
	size_t	index;

	if (!s1 || !set)
		return (0);
	index = 0;
	size = get_size(s1, set);
	string = (char *) ft_calloc(size + 1, sizeof(char));
	if (!string)
		return (0);
	if (size == 0)
		return (string);
	while (helper_is_in(set, *s1))
		s1++;
	while (index < size)
	{
		string[index] = s1[index];
		index++;
	}
	string[index] = '\0';
	return (string);
}
