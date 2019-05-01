# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 09:40:00 by ysan-seb          #+#    #+#              #
#    Updated: 2018/11/10 20:25:21 by ysan-seb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

FLAG = -Wall -Werror -Wextra

SRC = 	ft_atoi.c \
		ft_bzero.c \
		ft_dprintf.c \
		ft_dprintf.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_iscntrl.c \
		ft_isdigit.c \
		ft_isgraph.c \
		ft_islower.c \
		ft_isprint.c \
		ft_ispunct.c \
		ft_isspace.c \
		ft_isupper.c \
		ft_isxdigit.c \
		ft_itoa.c \
		ft_lstadd.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_printf.c \
		ft_fprintf.c \
		ft_printf_add_to_buffer.c \
		ft_printf_b.c \
		ft_printf_buffer_flush.c \
		ft_printf_c.c \
		ft_printf_cmaj.c \
		ft_printf_conversion.c \
		ft_printf_di.c \
		ft_printf_dmaj.c \
		ft_printf_getspace.c \
		ft_printf_length.c \
		ft_printf_modulo.c \
		ft_printf_o.c \
		ft_printf_omaj.c \
		ft_printf_p.c \
		ft_printf_parser.c \
		ft_printf_precision.c \
		ft_printf_putflags.c \
		ft_printf_remove_min.c \
		ft_printf_s.c \
		ft_printf_smaj.c \
		ft_printf_str_reverse.c \
		ft_printf_u.c \
		ft_printf_umaj.c \
		ft_printf_unicode.c \
		ft_printf_x.c \
		ft_printf_xmaj.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_sprintf.c \
		ft_stoa_base.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strjoin_free.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_utoa_base.c \
		ft_vdprintf.c \
		ft_vprintf.c \

OBJ = $(SRC:.c=.o)

DIR_HEADER = -I./

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c libft.h
	gcc -c -Wall -Wextra -Werror -o $@ -c $< -I./includes 

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	make

.PHONY: all clean fclean re