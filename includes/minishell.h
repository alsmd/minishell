/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:48:17 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/24 17:22:36 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

typedef enum e_relations
{
	PIPE = 1,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_OUTPUT_APPEND,
	REDIRECT_INPUT_DELIMITER
} e_relations;

typedef struct s_node
{
	char				**argv;
	char				*full_instruction;
	int					not_exist;
	int					input;
	int					output;
	char				*relation;
	struct s_node		*next;
	struct s_node		*previous;
}	t_node;

typedef struct s_minishell
{
	char		**paths;
	char		**operators;
	char		**env; 
	t_node		*node;

} t_minishell;

enum e_error
{
	ERROR_SINTAX = 1,
	ERROR_OPEN_FILE
};


void	make_shell_command(char *buffer);

//PARSES
int	parse_string(char *buffer);

//OPERATORS
int	output(t_node *cmd);



//UTILS
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);
void	handler_final_file(int fd);
char	*is_in(char **array, char *str);
char	*ft_strdup(const char *s);

#endif