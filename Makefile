# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maki <maki@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/23 22:00:58 by ysan-seb          #+#    #+#              #
#    Updated: 2019/05/02 16:20:48 by ysan-seb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ping

SRC_PATH = ./src/

SRCS =	$(SRC_PATH)main.c \
		$(SRC_PATH)ping.c \
		$(SRC_PATH)packet.c \
		$(SRC_PATH)time.c \

OBJS =	$(SRCS:.c=.o)

CC = gcc

FLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror

HEADER = -I./inc

LIBFT = libft/libft.a

RM = rm -rf

all	: lib $(NAME)

lib	:
	@make -C libft/

$(NAME):$(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(HEADER) $(LIBFT)

%.o: %.c ./inc/ft_ping.h ./inc/libft.h ./inc/libftprintf.h
	gcc $(FLAGS) -o $@ -c  $< $(HEADER)

clean	:
	@make -C libft/ clean
	$(RM) $(OBJS)

fclean: clean
	@make -C libft/ fclean
	$(RM) $(NAME)

re	:	fclean
	make

.PHONY: all lib clean fclean re
