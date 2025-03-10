# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 12:55:42 by ebansse           #+#    #+#              #
#    Updated: 2024/11/18 15:57:52 by ebansse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    = ft_nbr_base.c ft_put.c ft_puthex.c ft_printf.c 

NAME    = libftprintf.a

CC		= cc	

AR		= ar rcs

CFLAGS	= -Wall -Wextra -Werror

OBJS    =  ${SRCS:.c=.o}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

${NAME} : ${OBJS}
	${AR} ${NAME} ${OBJS}

all : ${NAME}

clean :
	rm -f ${OBJS} 

fclean : clean
	rm -f ${NAME}

re : fclean ${NAME}