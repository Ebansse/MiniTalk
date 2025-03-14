# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 12:55:42 by ebansse           #+#    #+#              #
#    Updated: 2025/03/14 15:30:14 by ebansse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = ft_nbr_base.c ft_put.c ft_puthex.c ft_printf.c 

NAME    = ftprintf.a

CC		= cc	

AR		= ar rcs

CFLAGS	= -Wall -Wextra -Werror -fPIC

OBJS    =  ${SRCS:.c=.o}

YELLOW = \033[0;33m
NC = \033[0m # No Color

all : ${NAME}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

${NAME} : ${OBJS}
	@${AR} ${NAME} ${OBJS}

clean :
	@rm -f ${OBJS}

fclean : clean
	@rm -f ${NAME}

re : fclean ${NAME}