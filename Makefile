# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/17 15:39:34 by lfabbro           #+#    #+#              #
#    Updated: 2017/02/06 17:59:17 by kboddez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 21sh

SRC_NAME	= main.c ft_init.c ft_parse.c ft_exec.c ft_banner.c\
			  ft_env.c ft_setenv.c ft_unsetenv.c ft_chdir.c ft_echo.c\
			  ft_where.c ft_tools.c ft_signal.c ft_exit.c ft_error.c\
			  ft_history.c ft_realloc_line.c ft_reset.c\
			  tcaps.c tcaps_history.c tcaps_check.c\
			  tcaps_delete.c tcaps_arrow.c tcaps_insert.c tcaps_ctrl.c \
			  tcaps_positions.c tcaps_cut_paste.c ft_realloc_tab.c \
				struct_tools.c struct_strsplit.c struct_strsplit_quote.c \
				struct_get_type.c remove_space.c \
				ft_cmds_split.c

#SRC_TERM_NAME = delete.c arrow.c insert.c ctrl.c

OBJ_NAME	= $(SRC_NAME:.c=.o)

LIB_NAME	= -lft

SRC_PATH 	= ./srcs/
OBJ_PATH	= ./objs/
TERM_PATH	= ./srcs/termcaps/
LIB_PATH 	= ./libft/
INC_PATH	= ./includes ./libft/includes ./libft/libft

SRC			= $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ			= $(SRC:.c=.o)
#SRC_TERM	= $(addprefix $(TERM_PATH),$(SRC_TERM_NAME))
#OBJ_TERM	= $(SRC_TERM:.c=.o)
LIB			= $(addprefix -L, $(LIB_PATH)) -lncurses
INC			= $(addprefix -I ,$(INC_PATH))

CC			= @gcc
CFLAGS		= -Wall -Wextra -Werror

RED			= \033[31;44m
GREEN		= \033[32;44m
ENDC		= \033[0m

all: lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(LIB_NAME)
	@(printf "$(GREEN) Make $(NAME) $(ENDC)\n")

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

.PHONY: all lib clean fclean re libfclean libclean

lib:
	@make -C ./libft

clean:
	@(printf "$(RED) Removing $(NAME) objects $(ENDC)\n")
	@rm -rfv $(OBJ) $(OBJ_PATH)

fclean: clean libfclean
	@(printf "$(RED) Removing $(NAME) executables $(ENDC)\n")
	@rm -fv $(NAME)

libclean:
	@(printf "$(RED) Removing $(LIB_PATH) objects $(ENDC)\n")
	@make -C ./libft clean

libfclean:
	@(printf "$(RED) Removing $(LIB_PATH) executables $(ENDC)\n")
	@make -C ./libft fclean

re: fclean
	@make all
