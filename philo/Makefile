# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akeldiya <akeldiya@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/23 12:39:15 by akeldiya          #+#    #+#              #
#    Updated: 2024/07/29 16:06:30 by akeldiya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Files
SRCS	= main.c	src/error.c	src/load_argv.c	src/initialize.c \
			src/process.c	src/free.c	src/helpers.c	src/get_set.c

# Sources and objects
OBJS	:= $(SRCS:%.c=%.o)

# Constant strings

NAME	= philo

CC = gcc

CFLAGS = -g -lpthread # -Wall -Wextra -Werror

RM = rm -f

# Rules

all: $(NAME)

%.o:	%.c
		${CC} ${CFLAGS} -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	${RM} ${OBJS}

fclean:		clean
	${RM} $(NAME)

re: fclean all

.PHONY:	 all clean fclean re
