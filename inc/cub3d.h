/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:47:57 by naokiiida         #+#    #+#             */
/*   Updated: 2025/02/18 03:14:57 by niida            ###   ########.fr       */
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
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <assert.h>

enum e_x_events {
 X_EVENT_KEY_PRESS = 2,
 X_EVENT_KEY_RELEASE = 3,
 X_EVENT_KEY_EXIT = 17
};

enum e_keys {
 KEY_ESC = 53,
 KEY_Q = 12,
 KEY_W = 13,
 KEY_A = 0,
 KEY_S = 1,
 KEY_D = 2,
 KEY_LEFT = 123,
 KEY_RIGHT = 124
};

# define TILE_SIZE 64
# define ROWS 11
# define COLS 15
# define WIDTH 800
# define HEIGHT 600
# define TEXTURE_WIDTH 10
# define TEXTURE_HEIGHT 10

// # define FOV_ANGLE 60 * (M_PI / 180)
// # define WALL_STRIP_WIDTH 1
// # define NUM_RAYS WIDTH / WALL_STRIP_WIDTH

enum e_map
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
	t_wall		tex_num;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	double		step;
}				t_texture;

typedef struct s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
}   t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			map[ROWS][COLS];
	t_img *buffer;
	t_player	*player;
	t_ray		*ray;
	t_texture	*texture;
	t_img		tile[4];
}				t_vars;

void			init(t_vars *vars);
int				raycasting(t_vars *vars);
void draw_buffer(t_vars *vars, int x);
void	draw(t_vars *vars);
int	close_display(t_vars *vars);
int	close_win(t_vars *vars);
int key_press(int key, t_vars *vars);
int key_release(int key, t_vars *vars);
void	buffer_mlx_pixel_put(t_img *buffer, int x, int y, int color);
void draw_map(t_vars *vars);
#endif
