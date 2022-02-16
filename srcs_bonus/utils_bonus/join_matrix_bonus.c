/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_matrix_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 12:54:06 by flda-sil             #+#    #+#             */
/*   Updated: 2022/02/16 12:54:07 by flda-sil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_bonus.h>

static void	copy_matrix(char **m1, char **m2, int *limiter, char **new_matriz)
{
	int		index;
	int		m1_index;
	int		m2_index;

	m2_index = 0;
	index = 0;
	while (index < *limiter)
	{
		new_matriz[index] = m1[index];
		index++;
	}
	m1_index = index + 1;
	while (m2[m2_index])
	{
		new_matriz[index] = m2[m2_index];
		m2_index += 1;
		index++;
	}
	*limiter = index;
	while (m1[m1_index])
	{
		new_matriz[index] = m1[m1_index];
		m1_index++;
		index++;
	}
}

int	matriz_size(char **m)
{
	int	index;

	index = 0;
	while (m[index])
		index++;
	return (index);
}

char	**join_matriz(char **m1, char **m2, int *limiter)
{
	int		size;
	char	**new_matriz;

	size = matriz_size(m1) + matriz_size(m2);
	new_matriz = (char **) ft_calloc(size + 1, sizeof(char *));
	copy_matrix(m1, m2, limiter, new_matriz);
	free(m1);
	free(m2);
	return (new_matriz);
}
