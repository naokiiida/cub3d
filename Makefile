NAME := cub3D

# CC := emcc
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
SRCS := main.c init.c ray_init.c ray_to_wall.c raycast.c draw.c move.c vector.c close.c file.c file_1.c file_2.c file_3.c file_4.c
# SRCS := file.c
OBJS := $(SRCS:%.c=$(ODIR)%.o)
DEPS = $(patsubst %.o,%.d, $(OBJS))
DEPFLAGS := -MMD -MP
CFLAGS = -Wall -Wextra -Werror $(DEPFLAGS)
INCS = -I$(IDIR) -I$(MLX) -I$(LIBFT) -I$(GNL)
LDFLAGS = -L$(MLX) -lmlx -L$(LIBFT) -lft -L$(GNL) -lgnl

ifeq ($(OS), Linux)
	MLX := minilibx-linux/
	LDFLAGS += -lXext -lX11 -lm
	CFLAGS += -D__LINUX__
endif
ifeq ($(OS), Darwin)
	# MLX := minilibx_mms_20200219/
	# MLXNAME := libmlx.dylib
	MLX := minilibx_opengl_20191021/
	LDFLAGS += -framework OpenGL -framework AppKit
	CFLAGS += -D__APPLE__
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
	@make $@ -C $(LIBFT)
	rm -rf $(ODIR)

fclean: clean
	@make $@ -C $(GNL)
	@make $@ -C $(LIBFT)
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: fclean
	@make all

pip: requirements.txt
	python3 -m pip list --outdated
	python3 -m pip install -U -r requirements.txt

norm:
	norminette $(SDIR) $(IDIR)
	nm -u $(NAME) | grep -v -E "_(open|close|read|write|printf|malloc|free|perror|strerror|exit|gettimeofday|sin|cos|tan|asin|acos|atan|atan2|sqrt|pow|ceil|floor|round|trunc|fabs|abs|mlx_init|mlx_new_window|mlx_new_image|mlx_put_image_to_window|mlx_loop|mlx_get_data_addr|mlx_destroy_image|mlx_destroy_window|mlx_hook|mlx_loop_hook|mlx_string_put|mlx_get_color_value|mlx_clear_window|mlx_pixel_put|mlx_key_hook|mlx_mouse_hook)@@"

fmt: $(SRCS)
	c_formatter_42 $(SDIR)*.c $(IDIR)*.h

deps:
	nm -u $(NAME)

l: fclean
	@make all WITH_LEAKS=1

san: fclean
	@make all WITH_ASAN=1 WITH_NDEF=1

# DO NOT RUN WITH_ASAN=1 WITH_NDEF=1, as it will conflict
drun: $(NAME)
	MallocGuardEdges=1 MallocCheckHeapStart=1 ./$(NAME)
v: all
	valgrind --leak-check=full --trace-children=yes ./$(NAME)

build: fclean
	@make all WITH_OPTIMIZATION=1

-include $(DEPS)

.PHONY: all clean fclean re mlx gnl libft re pip norm fmt deps l san v build drun
