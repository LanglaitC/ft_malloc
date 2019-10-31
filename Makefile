# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clanglai <clanglai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 13:42:54 by clanglai          #+#    #+#              #
#    Updated: 2019/10/31 13:56:31 by clanglai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
FLAGS=-Wall -Wextra -Werror
SRC_FILES=	ft_malloc.c \
			ft_free.c \
			ft_realloc.c
SRC_PATH=srcs
SRC= $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ=$(SRC:.c=.o)
ifeq ($(HOSTTYPE),) \
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: $(SRC)

%.o : %.c
	@$(CC) $(FLAGS) -o $@ -c $<