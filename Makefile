# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 13:42:54 by clanglai          #+#    #+#              #
#    Updated: 2019/11/02 14:56:00 by clanglai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
FLAGS=-Wall -Wextra -Werror -fPIC
SRC_FILES=	malloc.c \
			free.c \
			realloc.c
INC_PATH=inc
SRC_PATH=srcs
OBJ_PATH=obj
SRC=$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ=$(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME=libft_malloc_$(HOSTTYPE).so

all: $(NAME)

$(NAME): $(OBJ)
	gcc -shared -o $(NAME) $(OBJ)
	@ln -sf $(NAME) libft_malloc.so
	@echo "\033[1;34m$(NAME)\033[1;32m...compiled\t✓\033[0m"

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@echo "Compiling $<"
	@$(CC) $(FLAGS) -I $(INC_PATH) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
