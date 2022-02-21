/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:51:16 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

extern t_minishell	g_minishell;

void	print_char(char c, int size)
{
	while (size--)
		write(1, &c, 1);
}

void	divider(char c, int size)
{
	print_char('|', 1);
	print_char(c, size);
	print_char('|', 1);
	print_char('\n', 1);
}

void	indent(int c, int size)
{
	while (c <= size + 18)
	{
		printf(" ");
		c++;
	}
	printf("|\n");
}

int	get_square_size(t_node *node)
{
	int		index;
	char	**argv;
	int		len;
	int		size;

	size = 23;
	index = 0;
	argv = node->argv;
	while (argv[index])
	{
		len = ft_strlen(argv[index]) + 11;
		if (len > size)
			size = len + 2;
		index++;
	}
	len = ft_strlen(node->full_path) + 8;
	if (len > size)
		size = len + 2;
	if (node->subshell)
	{
		len = ft_strlen(node->subshell) + 5;
		if (len > size)
			size = len + 2;
	}
	return (size);
}

void	header_box(int size)
{
	print_char(' ', g_minishell.tab_indentation);
	print_char(' ', 1);
	print_char('_', size);
	print_char('\n', 1);
	print_char('>', g_minishell.tab_indentation);
	divider(' ', size);
}
