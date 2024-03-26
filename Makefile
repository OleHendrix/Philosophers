# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olehendrix <olehendrix@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 16:42:13 by ohendrix          #+#    #+#              #
#    Updated: 2024/03/26 23:55:56 by olehendrix       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SOURCES = \
main.c \
init.c \
getters.c \
routine.c \
utils.c \
utils2.c \

CFLAGS = -Wall -Werror -Wextra -fsanitize=thread

OBJS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C Libft/ all
	cc $(OBJS) $(CFLAGS) Libft/libft.a -o $(NAME) 

clean:
		rm -f $(OBJS)
		make -C Libft/ clean

fclean: clean
		rm -f $(NAME)
		make -C Libft/ fclean
		
re: fclean all

.PHONY: all, clean, fclean, re,