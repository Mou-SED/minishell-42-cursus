# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moseddik <moseddik@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/18 10:50:08 by moseddik          #+#    #+#              #
#    Updated: 2022/09/14 09:13:39 by moseddik         ###   ########.fr        #
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

# ******************************** Directories *********************************
INC_DIR			:= include
SRC_DIR			:= src
OBJ_DIR			:= obj
LIB_DIR			:= lib
LIBFT_DIR		:= $(LIB_DIR)/libft
tmp				:= /tmp/minishell
# ******************************** Readline lib ********************************

ILIB	=	-I$(LIB_DIR)/libreadline/$(INC_DIR)
SLIB	=	-L$(LIB_DIR)/libreadline -lreadline

# *********************************** Files ************************************
NAME			:= minishell
SRC				:= $(SRC_DIR)/main/main.c \
					$(SRC_DIR)/lexical_analysis/tokenizer.c \
					$(SRC_DIR)/lexical_analysis/linked_list_token.c \
					$(SRC_DIR)/lexical_analysis/tokenizer_utils.c \
					$(SRC_DIR)/lexical_analysis/cases_functions.c \
					$(SRC_DIR)/syntax_analysis/parsing.c \
					$(SRC_DIR)/syntax_analysis/ast.c \
					$(SRC_DIR)/syntax_analysis/Helper_functions.c \
					$(SRC_DIR)/signals_handler/signals_handler.c \
					$(SRC_DIR)/manag_error/ft_print_error.c \
					$(SRC_DIR)/manag_error/syntax_error_scan.c \
					$(SRC_DIR)/manag_error/check_syntax.c \
					$(SRC_DIR)/manag_error/heredoc_tools.c \
					$(SRC_DIR)/manag_error/heredoc.c \
					$(SRC_DIR)/expander/expander.c \
					$(SRC_DIR)/expander/expander_tools.c \
					$(SRC_DIR)/expander/expander_tools2.c \
					$(SRC_DIR)/expander/wild_card.c \
					$(SRC_DIR)/expander/wild_card_tools.c \
					$(SRC_DIR)/execution/Helper_functions.c \
					$(SRC_DIR)/execution/execution.c \
					$(SRC_DIR)/execution/built_in_cmd.c \
					$(SRC_DIR)/execution/tools.c \
					$(SRC_DIR)/execution/files_management.c \
					$(SRC_DIR)/environment/environment.c \
					$(SRC_DIR)/environment/environment_2.c \
					$(SRC_DIR)/environment/environment_3.c \
					$(SRC_DIR)/environment/environment_4.c \
					$(SRC_DIR)/execution/built_in_commands/cd_tools.c \
					$(SRC_DIR)/execution/built_in_commands/cd.c \
					$(SRC_DIR)/execution/built_in_commands/echo.c \
					$(SRC_DIR)/execution/built_in_commands/exit.c \
					$(SRC_DIR)/execution/built_in_commands/pwd.c \
					$(SRC_DIR)/execution/built_in_commands/unset.c \
					$(SRC_DIR)/execution/built_in_commands/env.c \
					$(SRC_DIR)/execution/built_in_commands/export.c \
					$(SRC_DIR)/execution/built_in_commands/export_tools.c \
					$(SRC_DIR)/execution/built_in_commands/export_tools2.c \
					$(SRC_DIR)/execution/child_work.c
OBJ				:= $(SRC:%.c=$(OBJ_DIR)/%.o)
INC				:= minishell.h
LIBFT			:= libft.a
LIBFT_SRC		:= $(shell ls $(LIBFT_DIR)/$(SRC_DIR))
LIBFT_INC		:= libft.h

# ****************************** Compiler Options ******************************
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -fsanitize=address
INCFLAGS		:= -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) $(ILIB)
LIBFLAGS		:= -L $(LIBFT_DIR) -lft $(SLIB)

# ******************************* Other commands *******************************
RM				:= rm -rf
MKDIR			:= mkdir -vp

# ******************************** Dependencies ********************************
INC_DEP			:= $(addprefix $(INC_DIR)/, $(INC))
LIBFT_DEP		:= $(LIBFT_DIR)/$(LIBFT)
LIBFT_SRC_DEP	:= $(addprefix $(LIBFT_DIR)/$(SRC_DIR)/, $(LIBFT_SRC))
LIBFT_INC_DEP	:= $(LIBFT_DIR)/$(INC_DIR)/libft.h

# ********************************** Targets ***********************************
all: $(NAME)

$(NAME): $(OBJ) $(INC_DEP) $(LIBFT_DEP)
	@echo "$(BLUE)Building	$(PURPLE)$(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(LIBFLAGS) -lncurses $(OBJ) -o $(NAME)
	@mkdir -p $(tmp)

$(OBJ_DIR)/%.o : %.c
	@$(MKDIR) $(dir $@)
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
	@$(RM) $(tmp)

re: fclean all

.PHONY: all clean fclean re
