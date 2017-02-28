
NAME				= 21sh

## ROOT FOLDER ##
SRC_SHELL_NAME		= main.c ft_init.c ft_parse.c ft_exec.c ft_signal.c \
					  ft_cmds_split.c
SRC_SHELL 			= $(addprefix shell/,$(SRC_SHELL_NAME))

## REDIRECTIONS FOLDER ##
SRC_RED_NAME 		= redir_iteration.c redir_output.c redir_file.c \
					  ft_create_file.c
SRC_RED 			= $(addprefix redirections/,$(SRC_RED_NAME))

## TOOLS FOLDER ##
SRC_TOOLS_NAME 		= ft_banner.c ft_error.c ft_realloc_line.c ft_realloc_tab.c \
					  ft_realloc_insert.c ft_tools.c ft_remove_space.c \
					  ft_free.c ft_new.c ft_tabzero.c ft_reset.c 
SRC_TOOLS			= $(addprefix tools/,$(SRC_TOOLS_NAME))

## STRUCT FOLDER ##
SRC_STRUCT_NAME		= struct_get_type.c struct_strsplit.c struct_strsplit_quote.c \
					  struct_strsplit_wo_quote.c struct_tools.c
SRC_STRUCT			= $(addprefix struct/,$(SRC_STRUCT_NAME))

## TCAPS FOLDER ##
SRC_TCAPS_NAME		= tcaps_init.c tcaps_paste.c tcaps.c tcaps_arrow.c \
					  tcaps_check.c tcaps_tools.c \
					  tcaps_cut_paste.c tcaps_delete.c tcaps_history.c \
					  tcaps_insert.c tcaps_positions.c tcaps_rewrite.c \
					  tcaps_ctrl_home_end.c tcaps_ctrl_arrow.c tcaps_clear.c
SRC_TCAPS			= $(addprefix tcaps/,$(SRC_TCAPS_NAME))

## BUILTINS FOLDER ##
SRC_BUILTINS_NAME	= ft_chdir.c ft_echo.c ft_env.c ft_exit.c ft_history.c \
					  ft_setenv.c ft_unsetenv.c ft_where.c
SRC_BUILTINS		= $(addprefix builtins/,$(SRC_BUILTINS_NAME))

## TOOLS FOLDER ##
SRC_TOOLS			= $(addprefix tools/,$(SRC_TOOLS_NAME))

## ALL FILES ##
SRC_NAME			= $(SRC_SHELL) $(SRC_RED) $(SRC_TOOLS) $(SRC_STRUCT) \
					  $(SRC_TCAPS) $(SRC_BUILTINS)

## BINARY FILES ##
OBJ_NAME			= $(SRC_NAME:.c=.o)

## LIBRARIES ##
LIB_NAME			= -lft

## PATHS ##
SRC_PATH 			= ./srcs/
OBJ_PATH			= ./objs/
LIB_PATH 			= ./libft/
INC_PATH			= ./includes ./libft/includes ./libft/libft

## PREFIX ##
SRC					= $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ					= $(SRC:.c=.o)
LIB					= $(addprefix -L, $(LIB_PATH)) -lncurses
INC					= $(addprefix -I ,$(INC_PATH))

## COMPILER ##
CC					= @gcc
CFLAGS				= -g -Wall -Wextra -Werror

## COLORS ##
RED					= \033[31;44m
GREEN				= \033[32;44m
ENDC				= \033[0m

.PHONY: all lib clean fclean re libfclean libclean

all: lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB) $(LIB_NAME)
	@(printf "$(GREEN) Make $(NAME) $(ENDC)\n")

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

lib:
	@(make -C ./libft)

clean:
	@(printf "$(RED) Removing $(NAME) objects $(ENDC)\n")
	@(rm -f $(OBJ) $(OBJ_PATH))

fclean: clean libfclean
	@(printf "$(RED) Removing $(NAME) executables $(ENDC)\n")
	@(rm -f $(NAME))

libclean:
	@(printf "$(RED) Removing $(LIB_PATH) objects $(ENDC)\n")
	@(make -C ./libft clean)

libfclean:
	@(printf "$(RED) Removing $(LIB_PATH) executables $(ENDC)\n")
	@(make -C ./libft fclean)

re: fclean all
