#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <dirent.h>
# include <colors_bonus.h>
# define TRUE 1
# define FALSE 0
# define PARENT 1
# define CHILD 2
# define IGNORE 3
# define M_UNK "\033[1;31mUnknown error!!!: I'm not programmed for this "
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
	char			**argv;
	char			*full_instruction;
	char			*full_path;
	int				not_exist;
	int				input;
	int				output;
	int				output_file;
	int				is_builtin;
	int				is_executable;
	int				is_absolute_path;
	char			*invalid_file;
	char			*subshell;
	char			*relation;
	struct s_node	*next;
	struct s_node	*previous;
}	t_node;

typedef struct s_fd
{
	int			value;
	struct s_fd	*next;
}	t_fd;

typedef struct s_folder
{
	char			*buffer;
	struct s_folder	*next;
	struct s_folder	*previous;
}	t_folder;

typedef struct s_debug
{
	int	show_nodes;
	int	show_subshell;
	int	exec_cmd;
}	t_debug;


typedef struct s_minishell
{
	int		exit_code;
	char	**paths;
	char	**operators;
	char	*asterisk_buffer;
	int		asterisk_found;
	int		has_signal;
	int		only_dir;
	char	*color;
	char	**matrix_env;
	int		debug_mode;
	int		debug_is_on;
	int		tab_indentation;
	t_debug	debug_flags;
	t_env	*env;
	t_node	*node;
	t_fd	*fds;
}	t_minishell;

enum e_error
{
	E_ERROR_SINTAX = 2,
	ERROR_OPEN_FILE,
	E_PERMISSION = 126,
	E_COMMAND_NOT_FOUND = 127,
};

// DEBUG
void		debuger(char **flags);
void		print_debuger_table(t_node *node);
void		show_nodes(t_node *node);
void		show_subshell(char *buffer);
void		debug_mode(char *buffer);
int			delete_flags(char *flag);
void		turn_on_debug_flags(char **flags);
void		print_flags(void);

// DEBUG UTILS
int			get_square_size(t_node *node);
void		indent(int c, int size);
void		divider(char c, int size);
void		print_char(char c, int size);

//Debug Module
void		header_box(int size);
void		module_name(t_node *node, int size);
void		module_relation(t_node *node, int size);
void		module_subshell(t_node *node, int size);
void		module_argv(char **matrix, int size);
void		footer_box(int size);

// INIT
void		init_shell(char **envp);
void		init_minishell(void);
void		init_term(void);
void		run(char *buffer);
void		hazzard(void);

// BUILTINS
void		exec_builtin(t_node *cmd);
int			is_builtin(t_node *cmd);
void		env(void);
void		export(char *command);
void		unset(char *key);
void		pwd(void);
void		cd(char **argv);
void		my_echo(char **argv);
void		my_exit(char **argv);
void		set_color(char *color);

// ENV
void		create_env(char **env);
void		add_variable(char *key, char *value);
char		**get_matrix(void);
char		*get_var_value(char *key);
int			get_variable_len(char *key);

// MESSAGES
void		show_error(char *name, char *message, int status, int has_to_exit);

// EXEC
void		make_shell_command(char *buffer);

// RELATIONS
void		link_relations(void);
char		*create_node(char *buffer, int *first, int index, char *relation);
char		*create_subshell(char *buffer);
void		create_relations(char *buffer);
void		toogle_space(int on);

// EXEC HELPER
void		validade_command(t_node *node);
int			get_status(int status);
void		close_prev_fd(t_node *node);
void		execute_subshell(t_node *node);

// FREE
void		clean_trash(void);
void		clean_node(void);
void		free_matrix(char **matrix);

// PARSES
int			parse_string(char *buffer);
void		toggle_quoute(char *buffer, char *quoute_is_on);
void		get_path(void);
int			is_comand(char *s);
void		trim_quotes(char **matrix);
char		**search_matrix(char **matrix);
char		*swap_chars(char *cmd, char to_find, char to_put);
void		check_absolute_path(t_node *cmd);
int			is_absolute_path(char *cmd);
char		*expand_vars(char *buffer);
int			check_grammar(void);
char		*copy_string_trim(char *string);
int			found_operator(char *buffer, int index, int direction);
int			found_operator_right(char *buffer, int index);
int			found_operator_left(char *buffer, int index);

int			another_parenthesis(char *buffer, int index);

// CHECK COMMAND
void		check_absolute_path(t_node *cmd);
void		check_command_exist(t_node *cmd);
int			is_command(t_node *node);

// OPERATORS
int			handle_output(t_node *cmd);
int			handle_input(t_node *cmd);
int			handle_pipe(t_node *node);
void		handle_here_doc(t_node *node);

//ASTERISK
void		get_asterisk_buffer(char *buffer, char *dir);
t_folder	*create_folder_list(char *buffer);
int			compare(char *string, char *filter);
t_folder	*add_to_list(t_folder **begin, char *buffer);
t_folder	*create_folder_list(char *buffer);
int			expand_asterisk(char *buffer, t_node *node, int *limiter);
void		search_directories(t_folder *list, char *dir);
void		search_filter(t_folder *list, char *dir);
DIR			*create_directory(t_folder *list, char *dir);
char		*make_path_previous(t_folder *list);
char		*make_path_next(t_folder *list);

// EXPAND ASTERISK HELPERS
char		*get_filter(char *buffer, int index);
int			get_filter_size(char *buffer);
void		add_result(t_folder *list, struct dirent *file);


// OPERATORS HELPERS
void		change_cmd_stdin(int fd, t_node *node);
void		write_and_free(int fd, char *line);
void		free_here_doc(char *line, char *delimiter);

// SIGNALS
void		signals(int sig);
void		set_signal(int *status);

// COMMAND HELPERS
t_node		*add_new_cmd(char *command, char *relation);
void		check_command_exist(t_node *cmd);
int			is_command(t_node *node);
void		add_fd(int fd);
int			get_status(int status);
void		expand_node(t_node *node);
void		chose_execute_line(t_node *node, int *status, int id);
void		execute_subshell(t_node *node);
void		exec_commands(t_node *node);

// UTILS
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*get_next_line(int fd);
void		handler_final_file(int fd);
char		*is_in(char **array, char *str);
char		*ft_strdup(const char *s);
char		*ft_strtrim(char *s1, char const *set);
void		close_fd(int fd);
int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
void		ft_strlcpy(char *dst, const char *src, size_t size);
int			has(char *string, char c);
char		**join_matriz(char **m1, char **m2, int *limiter);

#endif