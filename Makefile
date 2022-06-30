# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/18 10:50:08 by moseddik          #+#    #+#              #
#    Updated: 2022/06/30 11:24:03 by moseddik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# *********************************** Colors ***********************************
NC				:= \033[m
RED				:= \033[0;31m
GREEN			:= \033[1;32m
YELLOW			:= \033[1;33m
BLUE			:= \033[0;34m
PURPLE			:= \033[1;35m
CYAN			:= \033[1;36m

# ******************************** Readline lib ********************************

ILIB	=	-I$(shell brew --prefix readline)/include
SLIB	=	-L$(shell brew --prefix readline)/lib -lreadline

# ******************************** Directories *********************************
INC_DIR			:= include
SRC_DIR			:= src
OBJ_DIR			:= obj
LIB_DIR			:= lib
LIBFT_DIR		:= $(LIB_DIR)/libft

# *********************************** Files ************************************
NAME			:= minishell
SRC				:= $(SRC_DIR)/main/main.c \
					$(SRC_DIR)/lexical_analysis/scanner.c \
					$(SRC_DIR)/lexical_analysis/tokenizer.c \
					$(SRC_DIR)/syntax_analysis/parsing.c \
					$(SRC_DIR)/signals_handler/signals_handler.c
OBJ				:= $(SRC:.c=.o)
INC				:= minishell.h
LIBFT			:= libft.a
LIBFT_SRC		:= $(shell ls $(LIBFT_DIR)/$(SRC_DIR))
LIBFT_INC		:= libft.h

# ****************************** Compiler Options ******************************
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g
INCFLAGS		:= -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) $(ILIB)
LIBFLAGS		:= -L $(LIBFT_DIR) -lft $(SLIB)

# ******************************* Other commands *******************************
RM				:= rm -rf
MKDIR			:= mkdir -p

# ******************************** Dependencies ********************************
OBJ_DEP			:= $(addprefix $(OBJ_DIR)/, $(OBJ))
INC_DEP			:= $(addprefix $(INC_DIR)/, $(INC))
LIBFT_DEP		:= $(LIBFT_DIR)/$(LIBFT)
LIBFT_SRC_DEP	:= $(addprefix $(LIBFT_DIR)/$(SRC_DIR)/, $(LIBFT_SRC))
LIBFT_INC_DEP	:= $(LIBFT_DIR)/$(INC_DIR)/libft.h

# ********************************** Targets ***********************************
all: $(NAME)

$(NAME): $(OBJ) $(INC_DEP) $(LIBFT_DEP)
	@$(MKDIR) $(OBJ_DIR)
	@mv $(OBJ) $(OBJ_DIR)
	@echo "$(BLUE)Building	$(PURPLE)$(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(LIBFLAGS) -lncurses $(OBJ_DIR)/*.o -o $(NAME)

%.o : %.c
	@echo "$(GREEN)Compiling	$(YELLOW)$(shell basename $<)$(NC)"
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(LIBFT_DEP): $(LIBFT_SRC_DEP) $(LIBFT_INC_DEP)
	@echo "$(BLUE)Building	$(CYAN)$(LIBFT)$(NC)"
	@make -C $(LIBFT_DIR)

clean:
	@echo "$(RED)Removing$(BLUE)	$(LIBFT)Object files$(NC)"
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)Removing	$(YELLOW)Object files$(NC)"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Removing	$(BLUE)$(LIBFT)$(NC)"
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Removing	$(PURPLE)$(NAME)$(NC)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
