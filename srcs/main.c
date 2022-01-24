/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:52:37 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/24 21:44:13 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_minishell	g_minishell;

void	*set_string(char *src, char *dest)
{
	while (*dest)
	{
		*src = *dest;
		src++;
		dest++;
	}
}


void	init_minishell(void)
{
	ft_bzero(&g_minishell, sizeof(t_minishell));// || | && < > << >> 
	
	g_minishell.operators = (char **) ft_calloc(8, sizeof(char *));
	g_minishell.operators[0] = ft_strdup("|");
	g_minishell.operators[1] = ft_strdup("<<");
	g_minishell.operators[2] = ft_strdup(">>");
	g_minishell.operators[3] = ft_strdup("<");
	g_minishell.operators[4] = ft_strdup(">");
	g_minishell.operators[5] = ft_strdup("||");
	g_minishell.operators[6] = ft_strdup("&&");
	g_minishell.operators[7] = NULL;
}


int	main(int argc, char *argv[], char *env[])
{
	int		status;
	char	*buffer;

	init_minishell();
	g_minishell.env = env;
	while (1)
	{
		buffer = readline(">");
		if (!ft_strncmp(buffer, "exit", 4))
			return (0);
		add_history(buffer);
		//trata a string (eu do futuro)
		status = parse_string(buffer);
		if (status != 0)
			printf("Error Sintaxe\n");
		//...
		
		//Realiza a substituição dos metacharacteres (eu do futuro)

		//Cria a lista encadeada de comandos e os seus relacionamentos 
		if (status == 0)
			make_shell_command(buffer);
	}
	return (0);
}
