# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leothoma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/23 15:49:42 by leothoma          #+#    #+#              #
#    Updated: 2025/07/23 15:49:43 by leothoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -O1 

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m
BOLD = \033[1m

SRC_DIR = ./src
OBJ_DIR = ./obj
SRC = main.c \
      __EXEC_BOOT__.c \
      parsing_user_input1.c \
      parsing_user_input2.c \
      parsing_user_input3.c \
      parsing_user_input4.c \
      parsing_user_input5.c \
      parsing_user_input6.c \
      parsing_user_input7.c \
      search_list_utils1.c \
	  search_list_utils2.c \
      string_utils.c \
      clear_utils.c \
      clear_utils2.c \
      setup_signals.c \
      setup_signals2.c \
      init.c \
      join.c \
      builtin_fn1.c \
      builtin_fn2.c \
      builtin_fn3.c \
      builtin_fn4.c \
	  exec_main1.c \
	  exec_main2.c \
	  exec_helper1.c \
	  exec_helper2.c \
	  echo_utils.c \
	  exec_children_utils.c \
	  parser.c \
	  parser2.c \
	  parser3.c \
	  new_exec1.c \
	  new_exec2.c \
	  new_exec3.c \
	  new_exec4.c \
	  print_utils.c \
	  heredoc_utils.c \
	  heredoc_utils2.c \

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Objets
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BLUE)Linking object files and libft...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -lreadline
	@echo "$(GREEN)Compilation complete! ✅$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ || (echo "$(RED)Compilation failed!$(RESET)"; exit 1)
	@echo "$(GREEN)$< compiled successfully! ✅$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)Object directory created. $(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@make -s -C $(LIBFT_DIR)
	@echo "$(GREEN)libft compiled successfully! ✅$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make clean -s -C $(LIBFT_DIR)
	@echo "$(RED)Object files and libft cleaned. 🧹$(RESET)"

fclean: clean
	@echo "$(RED)Removing final executable...$(RESET)"
	@rm -rf $(NAME)
	@make fclean -s -C $(LIBFT_DIR)
	@echo "$(RED)Executable and libft cleaned. 🧹$(RESET)"

re: fclean all

.PHONY: all clean fclean re

