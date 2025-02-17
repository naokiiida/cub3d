/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:36:14 by sasano            #+#    #+#             */
/*   Updated: 2025/02/17 18:56:01 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_vars *vars)
{
    int i;
    int j;
    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "cub3d");
    vars->ray = (t_ray *)calloc(sizeof(t_ray));
    vars->player = (t_player *)calloc(sizeof(t_player));
    vars->map = (int **)malloc(sizeof(int *) * ROWS);
    vars->texture = (t_texture *)calloc(sizeof(t_texture));
    // 描画バッファの初期化
    vars->buffer->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
    vars->buffer->bits_per_pixel = 32;
    vars->buffer->line_length = WIDTH * 4;
    vars->buffer->endian = 0;
    vars->buffer->addr = mlx_get_data_addr(vars->buffer->img, &vars->buffer->bits_per_pixel, &vars->buffer->line_length, &vars->buffer->endian);

    vars->player->pos.x = 3.5;
    vars->player->pos.y = 3.5;
    vars->player->dir.x = -1;
    vars->player->dir.y = 0;
    vars->player->plane.x = 0;
    vars->player->plane.y = 0.66;
    vars->player->move_speed = 0.05;
    vars->player->rot_speed = 0.05;
    
    int map[ROWS][COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    i = 0;
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

    // 画像をロードし、画像のピクセルデータを取得
    
}
