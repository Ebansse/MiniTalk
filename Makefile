# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: GitHub Copilot <githubcopilot@student.42.fr>#+#  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 17:23:27 by GitHub Copilot    #+#    #+#              #
#    Updated: 2025/03/10 17:23:56 by GitHub Copilot   ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I/usr/include -Iprintf
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
	${MAKE} clean

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

make_serv: make_libs $(OBJ_SERVER)
	@echo "${BLUE}Compiling server...${NC}"
	@$(CC) $(OBJ_SERVER) $(CFLAGS) $(INCLUDES) -o $(SERVER) $(LIBS)
	@echo "${GREEN}Server compiled successfully!${NC}"

make_client: $(OBJ_CLIENT)
	@echo "${BLUE}Compiling client...${NC}"
	$(CC) $(OBJ_CLIENT) $(CFLAGS) $(INCLUDES) -o $(CLIENT) $(LIBS)
	@echo "${GREEN}Client compiled successfully!${NC}"

make_libs:
	@echo "${YELLOW}Compiling printf library...${NC}"
	make -C printf
	@echo "${GREEN}Printf library compiled successfully!${NC}"

clean:
	@echo "${RED}Cleaning object files...${NC}"
	@rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	@make -C printf clean
	@echo "${GREEN}Cleaned object files!${NC}"

fclean: clean
	@echo "${RED}Cleaning all binaries...${NC}"
	@rm -f $(SERVER) $(CLIENT)
	@make -C printf fclean
	@echo "${GREEN}Cleaned all binaries!${NC}"

re: fclean all
	${MAKE} clean

.PHONY: all clean fclean re