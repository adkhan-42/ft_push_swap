
NAME        = push_swap
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I src -I .
VALFLAG     = -g

LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

SRCS        = src/utils/input_utils.c \
              src/utils/input2_utils.c \
              src/utils/init_stack_a.c \
              src/utils/linked_list.c \
              src/utils/execute_move.c \
              src/utils/finder_utils.c \
              src/utils/error_utils.c \
              src/ops/push_ops.c \
              src/ops/swap_ops.c \
              src/ops/rotate_ops.c \
              src/ops/rev_rotate_ops.c \
              src/sort/sort_tiny.c \
              src/sort/sort.c \
              src/sort/turk_utils.c \
              src/main.c

OBJS        = $(SRCS:.c=.o)


all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(VALFLAG) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "✅ push_swap compiled successfully!"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR) --no-print-directory
	rm -f $(OBJS)
	@echo "🧹 Objects cleaned."

fclean: clean
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	rm -f $(NAME)
	@echo "🗑️  Executables removed."

re: fclean all

.PHONY: all clean fclean re