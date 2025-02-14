/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:36:14 by sasano            #+#    #+#             */
/*   Updated: 2025/02/15 03:36:28 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_vars *vars)
{
	int	i;
	int	j;
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

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "cub3d");
	vars->ray = (t_ray *)calloc(1, sizeof(t_ray));
	vars->player = (t_player *)calloc(1, sizeof(t_player));
	// vars->map = (int **)calloc(ROWS, sizeof(int *));
	vars->texture = (t_texture *)calloc(1, sizeof(t_texture));
	vars->player->pos.x = 3.5;
	vars->player->pos.y = 3.5;
	vars->player->dir.x = -1;
	vars->player->dir.y = 0;
	vars->player->plane.x = 0;
	vars->player->plane.y = 0.66;
	vars->player->move_speed = 0.05;
	vars->player->rot_speed = 0.05;
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
}
