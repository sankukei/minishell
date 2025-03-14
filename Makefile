NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -g3 -I.

SRC_DIR = ./src
OBJ_DIR = ./obj
SRC = main.c \
      __EXEC_BOOT__.c \
      parsing_user_input.c \
      search_list_utils.c
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

