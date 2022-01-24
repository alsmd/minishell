
SRCS =	./srcs/main.c \
		./srcs/utils/ft_calloc.c ./srcs/utils/ft_split.c ./srcs/utils/ft_bzero.c ./srcs/utils/ft_strlen.c ./srcs/utils/ft_strtrim.c \
		./srcs/utils/ft_substr.c ./srcs/utils/ft_strjoin.c ./srcs/utils/ft_strncmp.c ./srcs/utils/get_next_line.c \
		./srcs/utils/handler_final_file.c ./srcs/utils/is_in.c ./srcs/utils/ft_strdup.c \
		./srcs/command/command_operations.c ./srcs/parse/parse_string.c  ./srcs/operators/redirect.c ./srcs/command/helper_command.c \
		./srcs/operators/pipe.c

OBJS = $(SRCS:.c=.o)

HEADER = ./includes/ 

NAME = minishell

CFLAGS = 

CC = gcc

RM = rm -f

all: $(NAME)

%.o: %.c
	$(CC) -c -o $@ $< -I $(HEADER) $(CFLAGS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I $(HEADER) -o $@ $^ -lreadline

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	valgrind --leak-check=full ./$(NAME) here_doc ok 'cat' 'cat' fileout

.PHONY: fclean re clean all run