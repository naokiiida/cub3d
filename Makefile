NAME := cub3d

CC := cc
MKDIR := mkdir -p
OS = $(shell uname)
SDIR := src/
ODIR := obj/
IDIR := inc/
MLX := mlx/
MLXNAME := libmlx.a
ifeq ($(OS), Linux)
	MLX := minilibx-linux/
endif
ifeq ($(OS), Darwin)
	# MLX := minilibx_mms_20200219/
	# MLXNAME := libmlx.dylib
	MLX := minilibx_opengl_20191021/
endif

LIBFT := libft/
GNL := get_next_line/
SRCS := main.c init.c map.c raycasting.c draw.c
OBJS := $(SRCS:%.c=$(ODIR)%.o)
DEPS = $(patsubst %.o,%.d, $(OBJS))
DEPFLAGS := -MMD -MP
CFLAGS = -Wall -Wextra -Werror $(DEPFLAGS)
INCS = -I$(IDIR) -I$(MLX) -I$(LIBFT) -I$(GNL)
LDFLAGS = -L$(MLX) -lmlx -L$(LIBFT) -lft -L$(GNL) -lgnl

ifeq ($(OS), Linux)
	MLX := minilibx-linux/
	LDFLAGS += -lXext -lX11 -lm
	CFLAGS += -D__Linux__
endif
ifeq ($(OS), Darwin)
	# MLX := minilibx_mms_20200219/
	# MLXNAME := libmlx.dylib
	MLX := minilibx_opengl_20191021/
	LDFLAGS += -framework OpenGL -framework AppKit
	CFLAGS += -D__Apple__
endif

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
	CFLAGS += -O3 -march=native -ffast-math -flto
endif


# dev: mlx_check san

all: $(NAME)

mlx_check:
	@if [ ! -d "$(MLX)" ]; then \
		echo "Error: $(MLX) not found"; \
		exit 1; \
	fi

$(NAME): $(OBJS) | $(ODIR) mlx gnl libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

$(ODIR)%.o: $(SDIR)%.c | $(ODIR) mlx gnl libft
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $<

$(ODIR):
	@echo "Creating directory: $(ODIR)"
	$(MKDIR) $@

mlx:
	@make -C $(MLX)

gnl:
	@make -C $(GNL)

libft:
	@make -C $(LIBFT)

clean:
	@make $@ -C $(MLX)
	@make $@ -C $(GNL)
	rm -rf $(ODIR)

fclean: clean
	@make $@ -C $(GNL)
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

.PHONY: all clean fclean re mlx gnl libft
