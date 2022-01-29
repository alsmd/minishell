/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flda-sil <flda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:48:17 by flda-sil          #+#    #+#             */
/*   Updated: 2022/01/29 14:41:45 by flda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <signal.h>
# include <term.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# define TRUE 1
# define FALSE 0
# define PARENT 1
# define CHILD 2
# define M_COMMAND_NOT_FOUND ": command not found"
# define M_INVALID_FILE ": No such file or directory"
# define M_ERROR_SINTAX "sintax error near unexpected token "
# define M_PERMISSION ": Permission denied"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*previous;
}	t_env;

typedef struct s_node
{
	char				**argv;
	char				*full_instruction;
	char				*full_path;
	int					not_exist;
	int					input;
	int					output;
	int					is_builtin;
	int					is_executable;
	int					is_absolute_path;
	char				*relation;
	struct s_node		*next;
	struct s_node		*previous;
}	t_node;

typedef struct s_fd
{
	int			value;
	struct s_fd	*next;
}	t_fd;

typedef struct s_minishell
{
	int					exit_code;
	char				**paths;
	char				**operators;
	t_env				*env;
	t_node				*node;
	t_fd				*fds;
}	t_minishell;

enum e_error
{
	E_ERROR_SINTAX = 2,
	ERROR_OPEN_FILE,
	E_PERMISSION = 126,
	E_COMMAND_NOT_FOUND = 127,
};

void	init_shell(char **envp);
void	init_minishell(void);
void	init_term(void);

// BUILTINS
void	exec_builtin(t_node *cmd);
int		is_builtin(t_node *cmd);
void	env(void);
void	export(char *command);
void	unset(char *key);
void	pwd(void);
void	cd(char **argv);
void	my_echo(char **argv);
void	my_exit(char **argv);

// ENV
void	create_env(char **env);
void	add_variable(char *key, char *value);
char	**get_matrix(void);
char	*get_var_value(char *key);
int		get_variable_len(char *key);

//MESSAGES
void	show_error(char *name, char *message, int status, int has_to_exit);

// EXEC
void	make_shell_command(char *buffer);

// FREE
void	clean_trash(void);
void	clean_node(void);
void	free_matrix(char **matrix);

//PARSES
int		parse_string(char *buffer);
void	get_path(void);
int		is_comand(char *s);
void	trim_quotes(char **matrix);
char	**search_matrix(char **matrix);
char	*swap_chars(char *cmd, char to_find, char to_put);
void	check_absolute_path(t_node *cmd);
int		is_absolute_path(char *cmd);
char	*expand_vars(char *buffer);
int		check_grammar(void);

//CHECK COMMAND
void	check_absolute_path(t_node *cmd);
void	check_command_exist(t_node *cmd);
int		is_command(t_node *node);

//OPERATORS
int		handle_output(t_node *cmd);
int		handle_input(t_node *cmd);
int		handle_pipe(t_node *node);
void	handle_here_doc(t_node *node);

//SIGNALS
void	signals(int sig);

//COMMAND HELPERS
t_node	*add_new_cmd(char *command, char *relation);
void	check_command_exist(t_node *cmd);
int		is_command(t_node *node);
void	add_fd(int fd);
int		get_status(int status);

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
char	*ft_strtrim(char *s1, char const *set);
void	close_fd(int fd);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

#endif