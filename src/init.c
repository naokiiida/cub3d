/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:36:14 by naokiiida         #+#    #+#             */
/*   Updated: 2025/02/22 20:42:56 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_vars *vars)
{
	int	i;
	int	j;
	int map[ROWS][COLS] =
	{
{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
	};
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
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "cub3d");
	vars->ray = (t_ray *)calloc(1, sizeof(t_ray));
	vars->player = (t_player *)calloc(1, sizeof(t_player));
	// vars->map = (int **)calloc(ROWS, sizeof(int *));
	vars->texture = (t_texture *)calloc(1, sizeof(t_texture));
	// 描画バッファの初期化
	vars->buffer = (t_img *)calloc(1, sizeof(t_img));
	vars->buffer->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->buffer->bits_per_pixel = 32;
	vars->buffer->line_length = WIDTH * 4;
	vars->buffer->endian = 0;
	vars->buffer->addr = mlx_get_data_addr(vars->buffer->img,
			&vars->buffer->bits_per_pixel, &vars->buffer->line_length,
			&vars->buffer->endian);
	printf("init\n");
	// 画像のロードとピクセルデータの取得
    int k = 0;
	char *path[4] = {"img/redbrick.xpm", "img/wood.xpm", "img/greystone.xpm", "img/bluestone.xpm"};
    int tile_size[2] = {TEXTURE_WIDTH, TEXTURE_HEIGHT};
	while (k < 4)
    {
        vars->tile[k].bits_per_pixel = 32;
        vars->tile[k].line_length = WIDTH * 4;
        vars->tile[k].endian = 0;
        vars->tile[k].img = mlx_xpm_file_to_image(vars->mlx, path[k],
                &tile_size[0], &tile_size[1]);
        vars->tile[k].addr = mlx_get_data_addr(vars->tile[k].img,
                &vars->tile[k].bits_per_pixel, &vars->tile[k].line_length,
                &vars->tile[k].endian);
        k++;
    }

	vars->player->pos = (t_vector2d){22.0, 11.5};
	vars->player->dir = (t_vector2d){-1.0, 0.0};
	vars->player->plane = (t_vector2d){0.0, 0.66};
	vars->player->move_speed = 0.05;
	vars->player->rot_speed = 0.05;
	i = 0;
	// vars->map = map;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			vars->map[i][j] = map[i][j];
			j++;
		}
		i++;
	}
}
