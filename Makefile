NAME :=

SDIR := src/
ODIR := obj/
IDIR := inc
SRCS := main.c 
OBJS := $(SRCS:%.c=$(ODIR)%.o)
INCS = -I$(IDIR)
DEPS = $(patsubst %.o,%.d, $(OBJS))
DEPFLAGS := -MMD -MP
LDFLAGS := -l
CFLAGS = -Wall -Wextra -Werror $(DEPFLAGS)
CC := cc
MKDIR := mkdir -p
OS = $(shell uname)

ifdef WITH_LEAKS
	CFLAGS += -DLEAK_CHECK -g3 -O0
endif
ifdef WITH_ASAN
	CFLAGS += -fsanitize=address -g3 -O0
endif
ifdef WITH_NDEF
	CFLAGS += -fsanitize=undefined -g3 -O0
endif
ifeq ($(OS), Linux)
	LDFLAGS +=
	CFLAGS += -D__Linux__
endif
ifeq ($(OS), Darwin)
	LDFLAGS +=
	CFLAGS += -D__Apple__
endif

all: $(NAME)

$(NAME): $(OBJS) | $(ODIR)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(LDFLAGS)

$(ODIR)%.o:$(SDIR)%.c | $(ODIR)
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

$(ODIR):
	@echo "Creating directory: $(ODIR)"
	$(MKDIR) $@

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: fclean
	@make all

pip: requirements.txt
	python3 -m pip list --outdated
	python3 -m pip install -U -r requirements.txt

norm: $(SRCS) pip
	norminette $(SRCS)

fmt: $(SRCS) pip
	c_formatter_42 $(SRCS)*.c $(IDIR)*.h

deps:
	nm -u $(NAME)

l: fclean
	@make WITH_LEAKS=1

san: fclean
	@make WITH_ASAN=1 WITH_NDEF=1

v: all
	valgrind --leak-check=full --trace-children=yes ./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re
