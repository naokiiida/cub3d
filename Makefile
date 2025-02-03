NAME := cub3d

SDIR := src/
ODIR := obj/
IDIR := inc/
MLXDIR :=
MLXNAME :=
LIBFT := ../libft/
SRCS := main.c
OBJS := $(SRCS:%.c=$(ODIR)%.o)
INCS = -I$(IDIR) -I$(MLXDIR)
DEPS = $(patsubst %.o,%.d, $(OBJS))
DEPFLAGS := -MMD -MP
LDFLAGS := -L$(MLXDIR) -lmlx
# LDFLAGS := -L$(MLXDIR) -lmlx -L$(LIBFT) -lft
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
ifdef WITH_OPTIMIZATION
	CFLAGS += -03 -march=native -ffast-math -flto
endif

ifeq ($(OS), Linux)
	MLXDIR := minilibx-linux/
	MLXNAME := libmlx.a
	LDFLAGS += -lXext -lX11 -lm
	CFLAGS += -D__Linux__
endif
ifeq ($(OS), Darwin)
	MLXDIR := minilibx_mms_20200219/
	MLXNAME := libmlx.dylib
	LDFLAGS += -lmlx
	# LDFLAGS += -framework OpenGL -framework AppKit
	CFLAGS += -D__Apple__
endif

dev: mlx_check san

all: $(NAME)

mlx_check:
	@if [ ! -d "$(MLXDIR)" ]; then \
		echo "Error: $(MLXDIR) not found"; \
		exit 1; \
	fi

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
	@make all WITH_LEAKS=1

san: fclean
	@make all WITH_ASAN=1 WITH_NDEF=1

v: all
	valgrind --leak-check=full --trace-children=yes ./$(NAME)

build: fclean
	@make all WITH_OPTIMIZATION=1

-include $(DEPS)

.PHONY: all clean fclean re
