/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:36:14 by niida             #+#    #+#             */
/*   Updated: 2025/02/25 23:01:18 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>

static int	load_image(t_vars *vars, t_img *img, char *path)
{
	// img->img = mlx_png_file_to_image(vars->mlx, path, &img->img_width, &img->img_height);
	img->img = mlx_xpm_file_to_image(vars->mlx, path, &img->img_width,
			&img->img_height);
	if (!img->img)
	{
		err("load_image", "mlx_xpm_file_to_image failed");
		return (EXIT_FAILURE);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (EXIT_SUCCESS);
}

int	init(t_vars *vars)
{
	// int	i;
	// int	j;
	int k;
// 	char *path[4] = {"img/redbrick.xpm", "img/wood.xpm", "img/greystone.xpm", "img/bluestone.xpm"};
// 	int map[ROWS][COLS] =
// 	{
// {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
// {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
// {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
// {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
// {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
// {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
// {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
// {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
// {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
// {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
// {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
// {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
// {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
// {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
// {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
// {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
// {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
// {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
// {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
// {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
// {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
// {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
// {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
// {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
// 	};
	// {
	// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	// };
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		err("init", "failed mlx_init");
		return (EXIT_FAILURE);
	}
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "cub3d");
	if (!vars->win)
	{
		err("init", "failed mlx_new_window");
		free(vars->mlx);
		return (EXIT_FAILURE);
	}

	vars->ray = (t_ray *)calloc(1, sizeof(t_ray));
	// vars->texture = (t_texture *)calloc(1, sizeof(t_texture));

	// 描画バッファの初期化
	vars->buffer = (t_img *)calloc(1, sizeof(t_img));
	vars->buffer->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->buffer->img)
	{
		err("init", "failed mlx_new_image");
		mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
		return (EXIT_FAILURE);
	}
	vars->buffer->addr = mlx_get_data_addr(vars->buffer->img,
			&vars->buffer->bits_per_pixel, &vars->buffer->line_length,
			&vars->buffer->endian);
	printf("init\n");
	// 画像のロードとピクセルデータの取得
	k = -1;
	while (++k < 4)
		if (load_image(vars, &vars->tile[k], vars->path[k]) == EXIT_FAILURE)
		{
			while (--k >= 0)
				mlx_destroy_image(vars->mlx, vars->tile[k].img);
			mlx_destroy_image(vars->mlx, vars->buffer->img);
			mlx_destroy_window(vars->mlx, vars->win);
			free(vars->mlx);
			return (EXIT_FAILURE);
		}
	// vars->player = (t_player *)calloc(1, sizeof(t_player));
	// vars->player->pos = (t_vector2d){22.0, 11.5};
	// vars->player->dir = (t_vector2d){-1.0, 0.0};
	// i = 0;
	// while (i < vars->map_size.y)
	// {
	// 	j = 0;
	// 	while (j < vars->map_size.x)
	// 	{
	// 		vars->map[y][x] = map[y][x];
	// 		j++;
	// 	}
	// 	i++;
	// }
	return (EXIT_SUCCESS);
}
