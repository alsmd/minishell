/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_matrix_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:54:06 by flda-sil          #+#    #+#             */
/*   Updated: 2022/02/21 07:53:33 by gsilva-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	matriz_size(char **m)
{
	int	index;

	index = 0;
	while (m[index])
		index++;
	return (index);
}

static void	copy_matrix_merge(char **m1, char **m2, char **new_matriz)
{
	int		index;
	int		m2_index;

	m2_index = 0;
	index = 0;
	while (m1[index])
	{
		new_matriz[index] = m1[index];
		index++;
	}
	while (m2[m2_index])
	{
		new_matriz[index] = m2[m2_index];
		m2_index += 1;
		index++;
	}
}

char	**merge_matriz(char **m1, char **m2)
{
	int		size;
	char	**new_matriz;

	size = matriz_size(m1) + matriz_size(m2);
	new_matriz = (char **) ft_calloc(size + 1, sizeof(char *));
	copy_matrix_merge(m1, m2, new_matriz);
	free(m1);
	free(m2);
	return (new_matriz);
}