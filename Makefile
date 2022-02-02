NAME = minishell
NAME_BONUS = minishell_bonus

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

RM = rm -rf

INCLUDE = -I ./includes/
INCLUDE_BONUS = -I ./includes/

PATH_SRC = ./srcs/
PATH_MAIN = $(PATH_SRC)main/
PATH_COMMAND = $(PATH_SRC)command/
PATH_ENV = $(PATH_SRC)env/
PATH_OPERATOR = $(PATH_SRC)operators/
PATH_MESSAGE = $(PATH_SRC)message/
PATH_PARSE = $(PATH_SRC)parse/
PATH_BUILTINS = $(PATH_SRC)builtins/
PATH_UTILS = $(PATH_SRC)utils/
PATH_OBJS = ./objs/

PATH_SRC_BONUS = ./srcs_bonus/
PATH_MAIN_BONUS = $(PATH_SRC_BONUS)main/
PATH_COMMAND_BONUS = $(PATH_SRC_BONUS)command/
PATH_ENV_BONUS = $(PATH_SRC_BONUS)env/
PATH_OPERATOR_BONUS = $(PATH_SRC_BONUS)operators/
PATH_MESSAGE_BONUS = $(PATH_SRC_BONUS)message/
PATH_PARSE_BONUS = $(PATH_SRC_BONUS)parse/
PATH_BUILTINS_BONUS = $(PATH_SRC_BONUS)builtins/
PATH_UTILS_BONUS = $(PATH_SRC_BONUS)utils/
PATH_OBJS_BONUS = ./objs_bonus/

SRCS =	$(PATH_MAIN)main.c	$(PATH_MAIN)init.c $(PATH_MAIN)clean_trash.c\
		$(PATH_BUILTINS)env.c $(PATH_BUILTINS)check_builtin.c $(PATH_BUILTINS)pwd.c\
		$(PATH_BUILTINS)cd.c $(PATH_BUILTINS)my_exit.c $(PATH_BUILTINS)echo.c\
		$(PATH_COMMAND)execute_command.c $(PATH_COMMAND)helper_command.c $(PATH_COMMAND)check_command.c\
		$(PATH_COMMAND)relations.c $(PATH_COMMAND)exec_helper.c\
		$(PATH_ENV)create_env.c $(PATH_ENV)get_matrix.c\
		$(PATH_MESSAGE)errors.c\
		$(PATH_OPERATOR)pipe.c $(PATH_OPERATOR)redirect.c $(PATH_OPERATOR)signal.c\
		$(PATH_OPERATOR)redirect_helper.c\
		$(PATH_PARSE)parse_string.c $(PATH_PARSE)parse_quotes.c $(PATH_PARSE)get_path.c\
		$(PATH_PARSE)expand_vars.c $(PATH_PARSE)check_grammar.c\
		$(PATH_UTILS)ft_bzero.c $(PATH_UTILS)ft_calloc.c $(PATH_UTILS)ft_split.c\
		$(PATH_UTILS)ft_strdup.c $(PATH_UTILS)ft_strjoin.c $(PATH_UTILS)ft_strlen.c\
		$(PATH_UTILS)ft_strncmp.c $(PATH_UTILS)ft_strtrim.c $(PATH_UTILS)ft_substr.c \
		$(PATH_UTILS)get_next_line.c $(PATH_UTILS)handler_final_file.c $(PATH_UTILS)is_in.c\
		$(PATH_UTILS)close_fd.c	$(PATH_UTILS)ft_atoi.c $(PATH_UTILS)ft_itoa.c \
		$(PATH_UTILS)ft_strlcpy.c

SRCS_BONUS = $(PATH_MAIN_BONUS)main.c $(PATH_MAIN_BONUS)init.c $(PATH_MAIN_BONUS)clean_trash.c\
		$(PATH_BUILTINS_BONUS)env.c $(PATH_BUILTINS_BONUS)check_builtin.c $(PATH_BUILTINS_BONUS)pwd.c\
		$(PATH_BUILTINS_BONUS)cd.c $(PATH_BUILTINS_BONUS)my_exit.c $(PATH_BUILTINS_BONUS)echo.c\
		$(PATH_COMMAND_BONUS)execute_command.c $(PATH_COMMAND_BONUS)helper_command.c $(PATH_COMMAND_BONUS)check_command.c\
		$(PATH_COMMAND_BONUS)relations.c $(PATH_COMMAND_BONUS)exec_helper.c\
		$(PATH_ENV_BONUS)create_env.c $(PATH_ENV_BONUS)get_matrix.c\
		$(PATH_MESSAGE_BONUS)errors.c\
		$(PATH_OPERATOR_BONUS)pipe.c $(PATH_OPERATOR_BONUS)redirect.c $(PATH_OPERATOR_BONUS)signal.c\
		$(PATH_OPERATOR_BONUS)redirect_helper.c $(PATH_OPERATOR_BONUS)asterisk.c\
		$(PATH_PARSE_BONUS)parse_string.c $(PATH_PARSE_BONUS)parse_quotes.c $(PATH_PARSE_BONUS)get_path.c\
		$(PATH_PARSE_BONUS)expand_vars.c $(PATH_PARSE_BONUS)check_grammar.c\
		$(PATH_UTILS_BONUS)ft_bzero.c $(PATH_UTILS_BONUS)ft_calloc.c $(PATH_UTILS_BONUS)ft_split.c\
		$(PATH_UTILS_BONUS)ft_strdup.c $(PATH_UTILS_BONUS)ft_strjoin.c $(PATH_UTILS_BONUS)ft_strlen.c\
		$(PATH_UTILS_BONUS)ft_strncmp.c $(PATH_UTILS_BONUS)ft_strtrim.c $(PATH_UTILS_BONUS)ft_substr.c \
		$(PATH_UTILS_BONUS)get_next_line.c $(PATH_UTILS_BONUS)handler_final_file.c $(PATH_UTILS_BONUS)is_in.c\
		$(PATH_UTILS_BONUS)close_fd.c	$(PATH_UTILS_BONUS)ft_atoi.c $(PATH_UTILS_BONUS)ft_itoa.c \
		$(PATH_UTILS_BONUS)ft_strlcpy.c
		
OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRCS))

OBJS_BONUS = $(patsubst $(PATH_SRC_BONUS)%.c, $(PATH_OBJS_BONUS)%.o, $(SRCS_BONUS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) ./objs/*/*.o -o $(NAME) -lreadline

$(PATH_OBJS)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)builtins/
	@mkdir -p $(PATH_OBJS)command/
	@mkdir -p $(PATH_OBJS)env/
	@mkdir -p $(PATH_OBJS)message/
	@mkdir -p $(PATH_OBJS)operators/
	@mkdir -p $(PATH_OBJS)parse/
	@mkdir -p $(PATH_OBJS)utils/
	@mkdir -p $(PATH_OBJS)main/
	$(CC) $(CFLAGS) $(INCLUDE) -I. -c $< -o $@ -lreadline

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(INCLUDE_BONUS) ./objs_bonus/*/*.o -o $(NAME_BONUS) -lreadline

$(PATH_OBJS_BONUS)%.o: $(PATH_SRC_BONUS)%.c
	@mkdir -p $(PATH_OBJS_BONUS)
	@mkdir -p $(PATH_OBJS_BONUS)builtins/
	@mkdir -p $(PATH_OBJS_BONUS)command/
	@mkdir -p $(PATH_OBJS_BONUS)env/
	@mkdir -p $(PATH_OBJS_BONUS)message/
	@mkdir -p $(PATH_OBJS_BONUS)operators/
	@mkdir -p $(PATH_OBJS_BONUS)parse/
	@mkdir -p $(PATH_OBJS_BONUS)utils/
	@mkdir -p $(PATH_OBJS_BONUS)main/
	$(CC) $(CFLAGS) $(INCLUDE) -I. -c $< -o $@ -lreadline

clean:
	$(RM) $(PATH_OBJS)
	$(RM) $(PATH_OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: fclean all

re_bonus: fclean bonus

run: all
	clear && valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

run_bonus: bonus
	clear && valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell_bonus

.PHONY: all bonus run run_bonus re re_bonus clean fclean