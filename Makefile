# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 13:42:54 by clanglai          #+#    #+#              #
#    Updated: 2020/01/07 16:54:02 by clanglai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
FLAGS=-Wall -Wextra -Werror -fPIC
SRC_FILES=	malloc.c \
			free.c \
			realloc.c \
			utils.c \
			show_alloc_mem.c \
		calloc.c
INC_FILE=ft_malloc.h
INC_PATH=inc
SRC_PATH=srcs
OBJ_PATH=obj
SRC=$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ=$(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
INC=$(addprefix $(INC_PATH)/, $(INC_FILE))
LIB_PATH=libft
LIB_NAME=lftprintf
LIBC=$(addprefix $(LIB_PATH), $(LIB_NAME))

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
LIBEXTENSION=.so
SUBNAME=libft_malloc
NAME=$(SUBNAME)_$(HOSTTYPE)$(LIBEXTENSION)


all: $(LIBC) $(NAME)

$(LIBC):
	@make -C $(LIB_PATH)

$(NAME): $(OBJ) $(INC)
	@gcc -shared -o $(NAME) -L$(LIB_PATH) -$(LIB_NAME) $(OBJ) -g
	@ln -sf $(NAME) $(SUBNAME)$(LIBEXTENSION)
	@echo "\033[1;34m$(NAME)\033[1;32m...compiled\t✓\033[0m"

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@echo "Compiling $<"
	@$(CC) $(FLAGS) -I $(INC_PATH) -o $@ -c $<

clean:
	@make -C $(LIB_PATH) clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C $(LIB_PATH) fclean
	@rm -rf $(NAME)
	@rm -rf $(SUBNAME)$(LIBEXTENSION)

re: fclean all
