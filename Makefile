# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 13:42:54 by clanglai          #+#    #+#              #
#    Updated: 2019/11/01 16:53:46 by clanglai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
FLAGS=-Wall -Wextra -Werror
SRC_FILES=	malloc.c \
			free.c \
			realloc.c
SRC_PATH=srcs
SRC=$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ=$(SRC:.c=.o)
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
NAME=libft_malloc_$(HOSTTYPE).so

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[1;34m$(NAME)\033[1;32m...compiled\t✓\033[0m"

%.o:%.c
	@echo "Compiling $<"
	@$(CC) $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all