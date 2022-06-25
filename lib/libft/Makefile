# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moseddik <moseddik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 20:18:19 by moseddik          #+#    #+#              #
#    Updated: 2022/02/25 18:03:04 by moseddik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NONE = \033[0m
GREEN = \033[32m
YELLOW = \033[33m
GRAY = \033[2;37m
CURSIVE = \033[3m
RED = \033[0;31m

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard src/*.c) 

BONUS = $(wildcard src/bonus/*/*.c)

OBJDIR = src/obj_fdir

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${BONUS:.c=.o}

NAME = libft.a
HEADER = include

%.o: %.c
	@$(CC) $(CLFAGS) -c $^ -o $@ -I $(HEADER)

${NAME}: ${OBJS}
	@ar -rcs $@ $^
	@mkdir -p $(OBJDIR)
	@mv src/*.o $(OBJDIR)
	@echo " \n\t $(GREEN)The library is ready to use$(NONE) \n "
	
all: ${NAME} bonus

bonus: ${OBJS_BONUS}
	@ar -rc ${NAME} $^
	@mv src/bonus/*/*.o $(OBJDIR)
	@echo " \n\t $(GREEN)The bonus part of library is ready to use$(NONE) \n "
	
clean:
	@rm -rf $(OBJDIR)
	@echo " \n\t $(RED)The library is removed and all objects files$(NONE) \n "

fclean:	clean
	@rm -f ${NAME} 

re: fclean all

.PHONY: all fclean bonus clean re
