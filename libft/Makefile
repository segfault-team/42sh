# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfabbro <lfabbro@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/27 11:20:09 by lfabbro           #+#    #+#              #
#   Updated: 2016/09/21 13:54:48 by lfabbro          ###   ########.fr         #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

## SOURCES ##
PRINTF = ft_printf.c ftpf_lenght.c ftpf_parse.c ftpf_set.c\
		   ftpf_padding.c ftpf_conversions.c ftpf_handle_wchar.c\
		   ftpf_formats_00.c ftpf_formats_01.c ftpf_char.c ftpf_hex.c\
		   ftpf_int.c ftpf_octal.c ftpf_ptr.c ftpf_str.c\
		   ftpf_uint.c ftpf_wstr.c ftpf_wchar.c

OBJ_PRINTF = $(PRINTF:.c=.o)

LIBFT = ft_strlen.c ft_strstr.c ft_strcpy.c ft_strdup.c ft_strndup.c\
			   ft_strcat.c ft_strcmp.c ft_strncpy.c ft_strncat.c ft_strlcat.c\
			   ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c\
			   ft_itoa_base.c ft_imaxtoa_base.c ft_uimaxtoa_base.c ft_itoa.c\
			   ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
			   ft_issticky.c ft_isalpha_str.c ft_isexec.c\
			   ft_toupper.c ft_tolower.c\
			   ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c\
			   ft_memmove.c ft_memchr.c ft_memcmp.c ft_memdel.c ft_strnew.c\
			   ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c\
			   ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c\
			   ft_strtrim.c ft_strxtrim.c ft_strsplit.c\
			   ft_strsplit_quote.c ft_strxtrim_quote.c\
			   ft_free_tab.c ft_tablen.c ft_tabnew.c ft_tabdup.c ft_tabndup.c\
			   ft_tabcpy.c ft_tabcat.c ft_tabpop.c\
			   ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_puttab.c\
			   ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
			   ft_memalloc.c\
			   ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c\
			   ft_lstmap.c ft_wstrlen.c ft_abs.c ft_swap.c\
			   ft_realloc.c ft_getnbr.c ft_wchar_size.c\
			   ft_nbrlen.c ft_getchar.c\
			   ft_atol.c ft_atoll.c ft_isnbr.c\
			   get_next_line.c

OBJ_LIBFT = $(LIBFT:.c=.o)

## PATHS ##
SRC_PRINTF_PATH = ./ft_printf/
SRC_LIBFT_PATH = ./libft/
OBJ_PATH = ./objs/
INC_PATH = ./includes ./libft

CC = @gcc
CFLAGS = -Wall -Wextra -Werror

## OBJECTS ##
OBJS_PRINTF = $(addprefix $(OBJ_PATH),$(OBJ_PRINTF))
OBJS_LIBFT = $(addprefix $(OBJ_PATH),$(OBJ_LIBFT))

## INCLUDES ##
INC = $(addprefix -I,$(INC_PATH))

## COLORS ##
RED = "\033[31;44m"
BLUE = "\033[32;44m"
ENDC = "\033[0m"

.PHONY: makelibft clean fclean re norme

## RULES ##
all :
	@make $(NAME)

$(NAME): 
	@echo $(BLUE) "Making libft" $(ENDC)
	@make $(OBJS_PRINTF)
	@make $(OBJS_LIBFT)
	@ar -rcs $(NAME) $(OBJS_PRINTF) $(OBJS_LIBFT)
	@ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PRINTF_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(OBJ_PATH)%.o: $(SRC_LIBFT_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean :
	@echo $(RED) "Removing libft objs" $(ENDC)
	@/bin/rm -f $(OBJS_PRINTF)
	@/bin/rm -f $(OBJS_LIBFT)
	@/bin/rm -rf $(OBJ_PATH)

fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all

norme :
	norminette **/*.[ch]
