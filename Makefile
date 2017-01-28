# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/17 15:39:34 by lfabbro           #+#    #+#              #
#    Updated: 2017/01/26 13:30:58 by kboddez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRC_NAME = main.c ft_init.c ft_parse.c ft_exec.c\
		   ft_env.c ft_setenv.c ft_unsetenv.c ft_chdir.c ft_echo.c ft_where.c\
		   ft_tools.c ft_signal.c ft_exit.c ft_error.c ft_history.c ft_termcaps.c \
			realloc.c history_term.c

OBJ_NAME = $(SRC_NAME:.c=.o)

LIB_NAME = -lft

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
LIB_PATH = ./libft/
INC_PATH = ./includes ./libft/includes ./libft/libft

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
#OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
OBJ = $(SRC:.c=.o)
LIB = $(addprefix -L, $(LIB_PATH)) -lncurses
INC = $(addprefix -I ,$(INC_PATH))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: lib $(NAME)
#	@make $(NAME)

$(NAME): $(OBJ)
	@($(CC) -o $(NAME) $(OBJ) $(LIB) $(LIB_NAME))
	@(echo "\033[32;44m Make $(NAME) \033[0m")

%.o: %.c
	@($(CC) $(CFLAGS) -o $@ -c $< $(INC))

.PHONY: all lib clean fclean re libfclean libclean

lib:
	@make -C ./libft

clean:
	@echo "\033[31;44m Removing $(NAME) objects \033[0m"
	@rm -rfv $(OBJ) $(OBJ_PATH)

fclean: clean libfclean
	@echo "\033[31;44m Removing $(NAME) executables \033[0m"
	@rm -fv $(NAME)

libclean:
	@echo "\033[31;44m Removing $(LIB_PATH) objects \033[0m"
	@make -C ./libft clean

libfclean:
	@echo "\033[31;44m Removing $(LIB_PATH) executables \033[0m"
	@make -C ./libft fclean

re: fclean
	@make all
