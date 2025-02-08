/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 13:51:58 by niida             #+#    #+#             */
/*   Updated: 2025/02/08 20:30:24 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H
# include <stdint.h>
# include <math.h>
#include <stdlib.h>
# include <sys/time.h>

typedef enum tile
{
	BLANK = ' ',
	FLOOR = '0',
	WALL = '1',
	PLAYER_N = 'N',
	PLAYER_S = 'S',
	PLAYER_W = 'W',
	PLAYER_E = 'E'
}			e_tile;

typedef struct color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}			t_color;

typedef struct map
{
	char	*north_texture_path;
	char	*south_texture_path;
	char	*west_texture_path;
	char	*east_texture_path;
	t_color	floor;
	t_color	ceiling;
	e_tile	**tiles;
}			t_map;

typedef struct fov
{
	double_t	x;
	double_t	y;
	double_t	zoom;
	double_t	radian;
	double_t	distance;
	double_t	camera_plane;
	suseconds_t	tv_usec;
}			t_fov;

typedef enum window_size
{
	WIDTH = 1920,
	HEIGHT = 1080
}			e_window_size;

enum				e_event_trigger
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSELEFT = 6,
	ON_MOUSERIGHT = 7,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

# ifdef __Linux__

enum				e_keycode
{
	C = 99,
	PLUS = 61,
	MINUS = 45,
	ESC = 65307,
	ARROW_LEFT = 65361,
	ARROW_RIGHT = 65363,
	ARROW_DOWN = 65364,
	ARROW_UP = 65362
};
# elif __Apple__

enum				e_keycode
{
	C = 8,
	PLUS = 24,
	MINUS = 27,
	ESC = 53,
	ARROW_LEFT = 123,
	ARROW_RIGHT = 124,
	ARROW_DOWN = 125,
	ARROW_UP = 126
};

/* On MacOS - Cocoa (AppKit) and OpenGL - version,
	* minilibx has partial support of X11 events and doesn’t support X11 mask
	* (x_mask argument of mlx_hook is useless, keep it at 0).
	* https://harm-smits.github.io/42docs/libs/minilibx/events.html#mlx_hook
	*/
enum				e_mask
{
	MASK_NONE = 0L,
	ONLY_KEYPRESS = 1L << 0
};

# endif
double get_ray(t_fov fov, char **map, double ray_dir_x, double ray_dir_y, int map_width, int map_height);
char **convert_map(char **map_data, int rows, int cols);

#endif
