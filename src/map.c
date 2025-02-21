/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niida <niida@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 02:46:04 by niida             #+#    #+#             */
/*   Updated: 2025/02/18 03:14:48 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
void draw_map(t_vars *vars)
{
	int i;
	int j;
	int color;
	t_grid block;

	i = 0;
	block.x = 0;
	block.y = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (vars->map[i][j] == MAP_WALL)
				color = 0x999;
			else
				color = 0xF90;

			while (block.x % TEXTURE_WIDTH != 0)
			{
				while (block.y % TEXTURE_HEIGHT != 0)
				{
					buffer_mlx_pixel_put(vars->buffer, block.x, block.y, color);
					block.y++;
				}
				block.x++;
			}
			j++;
		}
		i++;
	}
}
