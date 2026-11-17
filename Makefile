NAME = push_swap

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = \
	bench.c \
	build.c \
	disorder.c \
	index.c \
	main.c \
	ops_push_rotate.c \
	ops_r_rotate.c \
	ops_swap.c \
	ops_utils.c \
	output.c \
	parse.c \
	parse_utils.c \
	sort_complex.c \
	sort_medium.c \
	sort_simple.c \
	stack_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
