# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebansse <ebansse@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/14 13:31:16 by ebansse           #+#    #+#              #
#    Updated: 2025/03/14 15:32:41 by ebansse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc	
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iprintf
LIBS = -Lprintf -l:ftprintf.a
SRC_CLIENT = client.c
SRC_SERVER = server.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
CLIENT = client
SERVER = server

# Colors
BLUE = \033[0;34m
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m # No Color

all : make_serv make_client
	@${MAKE} --no-print-directory clean

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

make_serv: make_libs $(OBJ_SERVER)
	@$(CC) $(OBJ_SERVER) $(CFLAGS) $(INCLUDES) -o $(SERVER) $(LIBS)
	@echo "${GREEN}Server compiled successfully!${NC}"

make_client: $(OBJ_CLIENT)
	@$(CC) $(OBJ_CLIENT) $(CFLAGS) $(INCLUDES) -o $(CLIENT) $(LIBS)
	@echo "${BLUE}Client compiled successfully!${NC}"

make_libs:
	@make --no-print-directory -C printf
	@echo "${YELLOW}Printf library compiled successfully!${NC}"

clean:
	@rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	@make --no-print-directory -C printf clean
	@echo "${RED}objects files cleaned !${NC}"

fclean: clean
	@rm -f $(SERVER) $(CLIENT)
	@make --no-print-directory -C printf fclean
	@echo "${RED}all binaries cleaned !${NC}"

re: fclean all
	@${MAKE} --no-print-directory clean