NAME := libgnl.a

SRCS := get_next_line.c get_next_line_utils.c
# SRCS := get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS := $(SRCS:.c=.o)
TEST_SRCS := main.c
CC := cc
CFLAGS := -Wall -Wextra -Werror
CSAN := -fsanitize=address -g3
BS := -D BUFFER_SIZE=1
# BS := -D BUFFER_SIZE=42
# BS := -D BUFFER_SIZE=10000000

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(BS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean
	@make all

.PHONY: all clean fclean re

test: all
	$(CC) $(TEST_SRCS) -L. -lgnl $(BS)
	@echo "--------------\n" && ./a.out

san: all
	$(CC) $(CFLAGS) $(CSAN) $(TEST_SRCS) -L. -lgnl $(BS)
	@echo "--------------" && ./a.out

out: all
	./a.out < test.txt | cat -e
n: all
	./a.out < newlines.txt | cat -e

