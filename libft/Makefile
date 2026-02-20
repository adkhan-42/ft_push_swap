NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
AR = ar rcs
GREEN = \033[32m
YELLOW = \033[33m
CYAN = \033[36m
RED = \033[31m
RESET = \033[0m

MAND_SRCS = ft_atoi.c \
            ft_bzero.c \
            ft_calloc.c \
            ft_isalnum.c \
            ft_isalpha.c \
			ft_isascii.c \
            ft_isdigit.c \
            ft_isprint.c \
			ft_itoa.c \
            ft_memchr.c \
            ft_memcmp.c \
            ft_memcpy.c \
            ft_memmove.c \
            ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
            ft_strchr.c \
            ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
            ft_strlcat.c \
            ft_strlcpy.c \
            ft_strlen.c \
			ft_strmapi.c \
            ft_strncmp.c \
            ft_strnstr.c \
            ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
            ft_tolower.c \
            ft_toupper.c

BONUS_SRCS = ft_lstadd_back.c \
			 ft_lstadd_front.c \
			 ft_lstclear.c \
			 ft_lstdelone.c \
			 ft_lstiter.c \
			 ft_lstlast.c \
			 ft_lstmap.c \
			 ft_lstnew.c \
			 ft_lstsize.c

MAND_OBJS = $(MAND_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

%.o: %.c libft.h
	@echo -e "$(GREEN)Creating Object File$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all bonus clean fclean re rebonus help index

all: $(NAME)

$(NAME): $(MAND_OBJS)
	@echo -e "$(GREEN)Making Library with Mandatory Files$(RESET)"
	$(AR) $(NAME) $(MAND_OBJS)

bonus: $(MAND_OBJS) $(BONUS_OBJS)
	@echo -e "$(GREEN)Adding Bonus files to Library$(RESET)"
	$(AR) $(NAME) $^

clean:
	@echo -e "$(RED)Cleaning all the Object Files$(RESET)"
	$(RM) $(MAND_OBJS) $(BONUS_OBJS)

fclean: clean
	@echo -e "$(RED)Removing the Library$(RESET)"
	$(RM) $(NAME)

re: fclean all
	@echo -e "$(GREEN)Recreated everything from Scratch excluding Bonus files$(RESET)"
	@echo -e "$(CYAN)To Add Bonus files to the library Plus run the bonus or the rebonus commands$(RESET)"

rebonus: fclean bonus
	@echo -e "$(GREEN)Included Bonus files in the rebuild$(RESET)"

help:
	@echo -e "$(CYAN)Available commands:"
	@echo "-------------------"
	@echo "make all     - Compiles the mandatory libft.a library."
	@echo "make bonus   - Compiles libft.a with all bonus functions."
	@echo "make clean   - Removes all object files (.o)."
	@echo "make fclean  - Removes all object files and the libft.a library."
	@echo "make re      - Rebuilds the mandatory library from scratch (fclean + all)."
	@echo "make rebonus - Rebuilds the library with the Bonus Functions (fclean + bonus)."
	@echo "make help    - Shows this help message."
	@echo "make index   - Shows index of all the functions included in libft (Manadatory + Bonus).$(RESET)"

index:
	@echo -e "$(RED)--- Mandatory Functions ---$(RESET)"
	@for file in $(MAND_SRCS); do \
		echo $$file; \
	done
	@echo ""
	@echo -e "$(YELLOW)--- Bonus Functions ---$(RESET)"
	@for file in $(BONUS_SRCS); do \
		echo $$file; \
	done

