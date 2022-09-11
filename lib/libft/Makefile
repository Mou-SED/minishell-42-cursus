# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zaabou <zaabou@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/21 20:18:19 by moseddik          #+#    #+#              #
#    Updated: 2022/09/11 18:48:34 by zaabou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *********************************** Colors ***********************************
NONE = \033[0m
GREEN = \033[32m
YELLOW = \033[33m
GRAY = \033[2;37m
CURSIVE = \033[3m
RED = \033[0;31m

# ******************************** Directories *********************************
INC_DIR		:= include
SRC_DIR		:= src
OBJ_DIR		:= obj
Minishell	:= ../../include/

# *********************************** Files ************************************
NAME		:= libft.a
SRC			:= $(SRC_DIR)/mandatory/ft_atoi.c \
				$(SRC_DIR)/mandatory/ft_bzero.c \
				$(SRC_DIR)/mandatory/ft_calloc.c \
				$(SRC_DIR)/mandatory/ft_isalnum.c \
				$(SRC_DIR)/mandatory/ft_isalpha.c \
				$(SRC_DIR)/mandatory/ft_isascii.c \
				$(SRC_DIR)/mandatory/ft_isdigit.c \
				$(SRC_DIR)/mandatory/ft_isprint.c \
				$(SRC_DIR)/mandatory/ft_itoa.c \
				$(SRC_DIR)/mandatory/ft_memchr.c \
				$(SRC_DIR)/mandatory/ft_memcmp.c \
				$(SRC_DIR)/mandatory/ft_memcpy.c \
				$(SRC_DIR)/mandatory/ft_memmove.c \
				$(SRC_DIR)/mandatory/ft_memset.c \
				$(SRC_DIR)/mandatory/ft_putchar_fd.c \
				$(SRC_DIR)/mandatory/ft_putendl_fd.c \
				$(SRC_DIR)/mandatory/ft_putnbr_fd.c \
				$(SRC_DIR)/mandatory/ft_putstr_fd.c \
				$(SRC_DIR)/mandatory/ft_split.c \
				$(SRC_DIR)/mandatory/ft_split_mode.c \
				$(SRC_DIR)/mandatory/ft_split_mode_helper.c \
				$(SRC_DIR)/mandatory/ft_strchr.c \
				$(SRC_DIR)/mandatory/ft_strdup.c \
				$(SRC_DIR)/mandatory/ft_striteri.c \
				$(SRC_DIR)/mandatory/ft_strjoin.c \
				$(SRC_DIR)/mandatory/ft_strlcat.c \
				$(SRC_DIR)/mandatory/ft_strlcpy.c \
				$(SRC_DIR)/mandatory/ft_strlen.c \
				$(SRC_DIR)/mandatory/ft_strmapi.c \
				$(SRC_DIR)/mandatory/ft_strcmp.c \
				$(SRC_DIR)/mandatory/ft_strncmp.c \
				$(SRC_DIR)/mandatory/ft_strnstr.c \
				$(SRC_DIR)/mandatory/ft_strstr.c \
				$(SRC_DIR)/mandatory/ft_strrchr.c \
				$(SRC_DIR)/mandatory/ft_strtrim.c \
				$(SRC_DIR)/mandatory/ft_substr.c \
				$(SRC_DIR)/mandatory/ft_tolower.c \
				$(SRC_DIR)/mandatory/ft_toupper.c
OBJ			:= ${SRC:%.c=$(OBJ_DIR)/%.o}
INC			:= libft.h

# ****************************** Compiler Options ******************************
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
INCFLAGS	:= -I $(INC_DIR)/$(INC) -I $(Minishell)

# ******************************* Other commands *******************************
RM			:= rm -rf
MKDIR		:= mkdir -vp

# ********************************** Targets ***********************************
all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $@ $^
	@echo " \n\t $(GREEN)The library is ready to use$(NONE) \n "

$(OBJ_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CLFAGS) -c $^ -o $@ $(INCFLAGS)

clean:
	@$(RM) $(OBJ_DIR)

fclean:	clean
	@$(RM) ${NAME}

re: fclean all

.PHONY: all fclean bonus clean re
