/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:47:57 by sasano            #+#    #+#             */
/*   Updated: 2025/02/14 23:26:08 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
// # include <mlx.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_LEFT				123
# define KEY_RIGHT				124

# define TILE_SIZE				64
# define ROWS					11
# define COLS					15
# define WIDTH				    800
# define HEIGHT					600

# define FOV_ANGLE				60 * (M_PI / 180)
# define WALL_STRIP_WIDTH		1
# define NUM_RAYS				WIDTH / WALL_STRIP_WIDTH

# define MINIMAP_SCALE_FACTOR	0.2

typedef enum axis{
    X_AXIS,
    Y_AXIS,
} e_axis;

typedef enum e_wall{
    NORTH_WALL,
    SOUTH_WALL,
    WEST_WALL,
    EAST_WALL,
}  e_wall;

typedef struct vector2d
{
	double	x;
	double	y;
}	t_vector2d;

typedef struct grid
{
	int	x;
	int	y;
}	t_grid;


typedef  struct   s_ray{
    t_vector2d dir;
    t_vector2d delta_dist;
    t_vector2d side_dist;
    t_grid map;
    t_grid step;
    int side;
    double perp_wall_dist;
}         t_ray;

typedef struct s_player
{
    t_vector2d pos;
    t_vector2d dir;
    t_vector2d plane;

    double move_speed;
    double rot_speed;
}   t_player;

typedef struct s_texture
{
    e_wall tex_num;
    int draw_start;
    int draw_end;
    int tex_x;
    double step;
}   t_texture;

typedef struct    s_vars{
    void *mlx;
    void *win;
    int map[ROWS][COLS];
    t_player *player;
    t_ray *ray;
}         t_vars;

void    init_vars(t_vars *vars);
void    raycasting(t_vars *vars)
#endif
