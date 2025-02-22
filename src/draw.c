/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:36:24 by naokiiida         #+#    #+#             */
/*   Updated: 2025/02/22 20:31:22 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// タイルのピクセルデータを取得する関数
unsigned int	get_tile_color(t_img *tile, int x, int y)
{
	char	*dst;

	dst = tile->addr + (y * tile->line_length + x * (tile->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

// 指定したピクセル位置に色を設定する関数
void	buffer_mlx_pixel_put(t_img *buffer, int x, int y, int color)
{
	char	*dst;

	// printf("arguments: %d, %d, %x\n", x, y, color);
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = buffer->addr + (y * buffer->line_length + x * (buffer->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

// 描画バッファに壁を描画
void	draw_buffer(t_vars *vars, int x)
{
	int				y;
	unsigned int	color;
	int				i;
	t_texture		*tex;

	tex = vars->texture;
	i = 0;
	//天井
	while (i < tex->draw_start)
		buffer_mlx_pixel_put(vars->buffer, x, i++, 0xAABBCC);
	//壁
	y = 0;
	// (void)y;
	while (i < tex->draw_end)
	{
		color = get_tile_color(&vars->tile[tex->id], tex->tex_x, y);
		// color = 0xAAAAAA;
		buffer_mlx_pixel_put(vars->buffer, x, i, color);
		i++;
		// 描画するタイルのy座標を更新
		y += tex->step;
	}
	//床
	while (i < HEIGHT)
		buffer_mlx_pixel_put(vars->buffer, x, i++, 0x0);
}

// 描画バッファを画面に描画
void	draw(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->buffer->img, 0, 0);
}
