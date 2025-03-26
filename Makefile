NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -g3 -I.

# Couleurs
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
      parsing_user_input.c \
      search_list_utils.c \
      string_utils.c \
      process_token_info.c \
      lexer.c \
	  clear_utils.c \
	  setup_signals.c

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Objets
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BLUE)Linking object files and libft...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft -lreadline
	@echo "$(GREEN)Compilation complete! ✅$(RESET)"
	@cat ./ascii/sky

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
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

