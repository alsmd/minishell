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
PATH_MAIN_BONUS = $(PATH_SRC_BONUS)main_bonus/
PATH_COMMAND_BONUS = $(PATH_SRC_BONUS)command_bonus/
PATH_ENV_BONUS = $(PATH_SRC_BONUS)env_bonus/
PATH_OPERATOR_BONUS = $(PATH_SRC_BONUS)operators_bonus/
PATH_MESSAGE_BONUS = $(PATH_SRC_BONUS)message_bonus/
PATH_PARSE_BONUS = $(PATH_SRC_BONUS)parse_bonus/
PATH_BUILTINS_BONUS = $(PATH_SRC_BONUS)builtins_bonus/
PATH_UTILS_BONUS = $(PATH_SRC_BONUS)utils_bonus/
PATH_OBJS_BONUS = ./objs_bonus/

SRCS =	$(PATH_MAIN)main.c	$(PATH_MAIN)init.c $(PATH_MAIN)clean_trash.c\
		$(PATH_BUILTINS)env.c $(PATH_BUILTINS)check_builtin.c $(PATH_BUILTINS)pwd.c\
		$(PATH_BUILTINS)cd.c $(PATH_BUILTINS)my_exit.c $(PATH_BUILTINS)echo.c\
		$(PATH_BUILTINS)set_color.c\
		$(PATH_COMMAND)execute_command.c $(PATH_COMMAND)helper_command.c $(PATH_COMMAND)check_command.c\
		$(PATH_COMMAND)relations.c $(PATH_COMMAND)exec_helper.c\
		$(PATH_ENV)create_env.c $(PATH_ENV)get_matrix.c\
		$(PATH_MESSAGE)errors.c $(PATH_MESSAGE)hazzard.c\
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

SRCS_BONUS = $(PATH_MAIN_BONUS)main_bonus.c $(PATH_MAIN_BONUS)init_bonus.c $(PATH_MAIN_BONUS)clean_trash_bonus.c\
		$(PATH_BUILTINS_BONUS)env_bonus.c $(PATH_BUILTINS_BONUS)check_builtin_bonus.c $(PATH_BUILTINS_BONUS)pwd_bonus.c\
		$(PATH_BUILTINS_BONUS)cd_bonus.c $(PATH_BUILTINS_BONUS)my_exit_bonus.c $(PATH_BUILTINS_BONUS)echo_bonus.c\
		$(PATH_BUILTINS_BONUS)set_color_bonus.c\
		$(PATH_COMMAND_BONUS)execute_command_bonus.c $(PATH_COMMAND_BONUS)helper_command_bonus.c $(PATH_COMMAND_BONUS)check_command_bonus.c\
		$(PATH_COMMAND_BONUS)relations_bonus.c $(PATH_COMMAND_BONUS)relations_helper_bonus.c $(PATH_COMMAND_BONUS)exec_helper_bonus.c\
		$(PATH_COMMAND_BONUS)make_commands_bonus.c\
		$(PATH_ENV_BONUS)create_env_bonus.c $(PATH_ENV_BONUS)get_matrix_bonus.c\
		$(PATH_MESSAGE_BONUS)errors_bonus.c $(PATH_MESSAGE_BONUS)hazzard_bonus.c $(PATH_MESSAGE_BONUS)debuger_bonus.c\
		$(PATH_OPERATOR_BONUS)pipe_bonus.c $(PATH_OPERATOR_BONUS)redirect_bonus.c $(PATH_OPERATOR_BONUS)signal_bonus.c\
		$(PATH_OPERATOR_BONUS)redirect_helper_bonus.c $(PATH_OPERATOR_BONUS)asterisk_bonus.c $(PATH_OPERATOR_BONUS)asterisk_helper_bonus.c\
		$(PATH_OPERATOR_BONUS)asterisk_result_bonus.c\
		$(PATH_PARSE_BONUS)parse_string_bonus.c $(PATH_PARSE_BONUS)parse_quotes_bonus.c $(PATH_PARSE_BONUS)get_path_bonus.c\
		$(PATH_PARSE_BONUS)expand_vars_bonus.c $(PATH_PARSE_BONUS)check_grammar_bonus.c $(PATH_PARSE_BONUS)expand_asterisk_bonus.c\
		$(PATH_PARSE_BONUS)expand_asterisk_helper_bonus.c $(PATH_PARSE_BONUS)parse_utils_bonus.c\
		$(PATH_UTILS_BONUS)ft_bzero_bonus.c $(PATH_UTILS_BONUS)ft_calloc_bonus.c $(PATH_UTILS_BONUS)ft_split_bonus.c\
		$(PATH_UTILS_BONUS)ft_strdup_bonus.c $(PATH_UTILS_BONUS)ft_strjoin_bonus.c $(PATH_UTILS_BONUS)ft_strlen_bonus.c\
		$(PATH_UTILS_BONUS)ft_strncmp_bonus.c $(PATH_UTILS_BONUS)ft_strtrim_bonus.c $(PATH_UTILS_BONUS)ft_substr_bonus.c \
		$(PATH_UTILS_BONUS)get_next_line_bonus.c $(PATH_UTILS_BONUS)handler_final_file_bonus.c $(PATH_UTILS_BONUS)is_in_bonus.c\
		$(PATH_UTILS_BONUS)close_fd_bonus.c	$(PATH_UTILS_BONUS)ft_atoi_bonus.c $(PATH_UTILS_BONUS)ft_itoa_bonus.c \
		$(PATH_UTILS_BONUS)ft_strlcpy_bonus.c $(PATH_UTILS_BONUS)compare_bonus.c $(PATH_UTILS_BONUS)join_matrix_bonus.c
		
OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRCS))

OBJS_BONUS = $(patsubst $(PATH_SRC_BONUS)%.c, $(PATH_OBJS_BONUS)%.o, $(SRCS_BONUS))

all: $(NAME)

message:
	@echo "\033[1;35mCompiling Shell\033[0m"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDE) ./objs/*/*.o -o $(NAME) -lreadline
	@echo "\033[1;32mREADY TO LAUNCH\033[0m"

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
	@$(CC) $(CFLAGS) $(INCLUDE) -I. -c $< -o $@ -lreadline

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(INCLUDE_BONUS) ./objs_bonus/*/*.o -o $(NAME_BONUS) -lreadline
	@echo "\033[1;32mREADY TO LAUNCH\033[0m"

$(PATH_OBJS_BONUS)%.o: $(PATH_SRC_BONUS)%.c
	@mkdir -p $(PATH_OBJS_BONUS)
	@mkdir -p $(PATH_OBJS_BONUS)builtins_bonus/
	@mkdir -p $(PATH_OBJS_BONUS)command_bonus/
	@mkdir -p $(PATH_OBJS_BONUS)env_bonus/
	@mkdir -p $(PATH_OBJS_BONUS)message_bonus/
	@mkdir -p $(PATH_OBJS_BONUS)operators_bonus/
	@mkdir -p $(PATH_OBJS_BONUS)parse_bonus/
	@mkdir -p $(PATH_OBJS_BONUS)utils_bonus/
	@mkdir -p $(PATH_OBJS_BONUS)main_bonus/
	@$(CC) $(CFLAGS) $(INCLUDE) -I. -c $< -o $@ -lreadline

clean:
	@echo "\033[1;33mCleaning objects\033[0m"
	@$(RM) $(PATH_OBJS)
	@$(RM) $(PATH_OBJS_BONUS)
	@echo "\033[1;32mDone!\033[0m"

fclean: clean
	@echo  "\033[1;33mCleaning all\033[0m"
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@echo  "\033[1;33mCleaning binaries\033[0m"
	@echo "\033[1;32mDone!\033[0m"

re: fclean all

re_bonus: fclean bonus

run:
	make re && valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell

run_bonus:
	make re_bonus && valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell_bonus

.PHONY: all bonus run run_bonus re re_bonus clean fclean