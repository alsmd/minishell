/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsilva-v <gsilva-v@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:48:17 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/25 11:04:06 by gsilva-v         ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;

	struct s_env	*next;
	struct s_env	*previous;
} t_env;

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
	t_env		*env;
	t_node		*node;

} t_minishell;

enum e_error
{
	ERROR_SINTAX = 1,
	ERROR_OPEN_FILE
};

// BUILTINS
void	env(void);
void	export(char *command);
void	unset(char *key);

// ENV
void	create_env(char **env);
void	add_variable(char *key, char *value);

void	make_shell_command(char *buffer);

//PARSES
int		parse_string(char *buffer);

int is_comand(char *s);
char **trim_quotes(char **matrix);
char **search_matrix(char **matrix);
char *swap_chars(char *cmd, char to_find, char to_put);

//OPERATORS
int		handle_output(t_node *cmd);
int		handle_pipe(t_node *node);

//OPERATORS HELPERS
t_node	*add_new_cmd(char *command, char *relation);
void	check_command_exist(t_node *cmd);
void	execute_cmd(t_node *cmd);
void	last_child(t_node *node);
void	parent(t_node *cmd, int fd[2]);

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
char	*ft_strtrim(char const *s1, char const *set);

#endif