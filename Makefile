NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -g3 -I. -O1 -fsanitize=address,undefined,signed-integer-overflow,null,leak,bounds -fno-omit-frame-pointer

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
      parsing_user_input1.c \
      parsing_user_input2.c \
      parsing_user_input3.c \
      parsing_user_input4.c \
      parsing_user_input5.c \
      parsing_user_input6.c \
      search_list_utils1.c \
	  search_list_utils2.c \
      string_utils.c \
      clear_utils.c \
      clear_utils2.c \
      setup_signals.c \
      init.c \
      join.c \
      builtin_fn1.c \
      builtin_fn2.c \
      builtin_fn3.c \
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
	  print_utils.c \

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
	@$(CC) $(CFLAGS) -c $< -o $@ || (echo "$(RED)Compilation failed!$(RESET)"; cat ./ascii/prankex; exit 1)
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

