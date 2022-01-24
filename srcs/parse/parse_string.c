/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:58:23 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/24 21:39:29 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_minishell g_minishell;

int string_forward(char *string, char c, int *i)
{
    int index;

    index = 1;
    *i += 1;
    while (string[index] != c && string[index])
        index++;
    if (string[index] == c)
        *i += 1;
    return (index);
}

int check_quotes(char *s)
{
    int i;
    int quote_s;
    int quote_d;
    
    i = 0;
    quote_s = 0;
    quote_d = 0;
    while (s[i])
    {
        if (s[i] == '\'')
            i += string_forward(&s[i], '\'', &quote_s);
        if (s[i] == '\"')
            i += string_forward(&s[i], '\"', &quote_d);
        i++;
    }
    if (quote_s % 2 != 0 || quote_d % 2 != 0)
        return (1);
    return(0);
}

int	parse_string(char *buffer)
{
	if (check_quotes(buffer))
		return (ERROR_SINTAX);
	while (*buffer)
	{
		if (!ft_strncmp(buffer, ">>>", 3))
			return (ERROR_SINTAX);
		if (*buffer == '\\')
			return (ERROR_SINTAX);
		if (*buffer == ';')
			return (ERROR_SINTAX);
		buffer++;
	}
	return (0);
}
