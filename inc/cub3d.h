/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:47:57 by naokiiida         #+#    #+#             */
/*   Updated: 2025/03/05 17:45:43 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// # include <mlx.h>
# include "libft.h"
# include "mlx.h"
# include <assert.h>

enum			e_x_events
{
	EVENT_KEY_PRESS = 2,
	EVENT_KEY_RELEASE = 3,
	EVENT_KEY_EXIT = 17
};

enum			e_x_masks
{
	M_KEY_PRESS = 1L << 0,
	M_KEY_RELEASE = 1L << 1,
	M_STRUCTURE_NOTIFY = 1L << 17,
};

enum			e_keys
{
	KEY_ESC = 53,
	KEY_Q = 12,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_LEFT = 123,
	KEY_RIGHT = 124
};

// # define TILE_SIZE 64
// # define ROWS 24
// # define COLS 24
// # define ROWS 11
// # define COLS 15
# define WIDTH 640
# define HEIGHT 480
// has to be power of 2 for & (TEXTURE_HEIGHT - 1) wrap around to work
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

// # define FOV_ANGLE 60 * (M_PI / 180)
// # define WALL_STRIP_WIDTH 1
// # define NUM_RAYS WIDTH / WALL_STRIP_WIDTH

enum			e_map
{
	MAP_WALL = 1,
	MAP_BLANK = 0
};

# define MINIMAP_SCALE_FACTOR 0.2

typedef enum e_axis
{
	X_AXIS,
	Y_AXIS,
}				t_axis;

typedef enum e_wall
{
	NORTH_WALL,
	SOUTH_WALL,
	WEST_WALL,
	EAST_WALL,
}				t_wall;

typedef struct vector2d
{
	double		x;
	double		y;
}				t_vector2d;

typedef struct grid
{
	int			x;
	int			y;
}				t_grid;

typedef struct s_ray
{
	t_vector2d	dir;
	t_vector2d	delta_dist;
	t_vector2d	side_dist;
	t_grid		grid;
	t_grid		step;
	int			side;
	double		perp_wall_dist;
}				t_ray;

typedef struct s_player
{
	t_vector2d	pos;
	t_vector2d	dir;
	t_vector2d	plane;

	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct s_texture
{
	t_wall		id;
	int			draw_start;
	int			draw_end;
	int			line_height;
	int			tex_x;
	double		step;
	int			ceiling_color;
	int			floor_color;
}				t_texture;

typedef struct s_img
{
	void		*img;
	char		*addr;

	int			*data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		*buffer;
	t_grid		map_size;
	int			**map;
	t_player	*player;
	t_ray		*ray;
	t_texture	*texture;
	char		*path[4];
	t_img		tile[4];
}				t_vars;

int				get_input(char *file, t_vars *vars);
int				err(char *function_name, const char *msg);
int				init(t_vars *vars);
int				raycasting(t_vars *vars);
void			draw_buffer(t_vars *vars, int x);
void			draw(t_vars *vars);
int				close_display(t_vars *vars);
int				close_win(t_vars *vars);
int				key_press(int key, t_vars *vars);
int				key_release(int key, t_vars *vars);
void			buffer_mlx_pixel_put(t_img *buffer, int x, int y, int color);
void			draw_map(t_vars *vars);
t_vector2d		vector_add(t_vector2d v1, t_vector2d v2);
t_vector2d		vector_scale(t_vector2d v, double scale);
t_vector2d		vector_rotate(t_vector2d v, double angle);
void			init_ray(t_vars *vars, int x);
void			calculate_perp_wall_dist(t_ray *ray);
void			calculate_wall_size(t_ray *ray, t_texture *texture);
void			decide_draw_texture(t_ray *ray, t_texture *texture);
int				get_texture_x(t_ray *ray, t_player *player);
/* File Processing - Main Public Functions */
int				read_elements(int fd, t_vars *vars);
int				get_input(char *file, t_vars *vars);

/* Utility Functions */
int				ft_atoi_mod(const char *str);
int				ft_strcmp(const char *str1, const char *str2);

// /* Internal Helpers - file.c */
// /* These functions are only used within file.c */
// int				initialize_vars(t_vars *vars);
// int				process_map_data(int fd, char **map_data);
// int				read_map_data(int fd, char **map_data);
// int				skip_blank_lines(int fd, char **map_data);

// /* Internal Helpers - file_1.c */
// /* These functions support element parsing */
// int				check_elements(char *line, t_texture *tex, char *path[4]);
// void			free_string_array(char **arr);
int				handle_texture_path(char **kv, char **path_ptr);
// _Bool			is_all_elements_loaded(t_vars *vars);
// int				process_key(int i, t_texture *tex, char *line);

// /* Internal Helpers - file_2.c and file_3.c */
// /* These functions support map and texture handling */
// int				count_strings(char **arr);
int				parse_rgb(int *color, char *input);
// int				process_cell(char c, t_vars *vars, int *curr_cols);
void			remove_trailing(char *line, char delim);
// int				set_player(t_vars *vars, int x, int y, char c);
int				validate_file(char *file, const char *expect_ext);

// /* Internal Helpers - file_4.c */
// /* These functions support map setup and validation */
int				load_map(char *map_data, t_vars *vars);
int				setup_map(char *map_data, t_vars *vars);
int	free_n_err(char *function_name, const char *msg, char **rgb);

#endif
