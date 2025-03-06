/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <sasano@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:36:24 by niida             #+#    #+#             */
/*   Updated: 2025/03/06 16:56:48 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_tile_color(t_img *tile, int x, int y)
{
	char	*dst;

	dst = tile->addr + (y * tile->line_length + x * (tile->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	buffer_mlx_pixel_put(t_img *buffer, int x, int y, int color)
{
	char	*dst;

	if (!(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT))
		return ;
	dst = buffer->addr
		+ (y * buffer->line_length + x * (buffer->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_buffer(t_vars *vars, int x)
{
	int				tex_y;
	double			tex_pos;
	unsigned int	color;
	int				i;
	t_texture		*tex;

	tex = vars->texture;
	i = 0;
	while (i < tex->draw_start)
		buffer_mlx_pixel_put(vars->buffer, x, i++, tex->ceiling_color);
	tex_pos = (tex->draw_start - HEIGHT / 2 + tex->line_height / 2) * tex->step;
	tex_y = 0;
	while (i < tex->draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += tex->step;
		color = get_tile_color(&vars->tile[tex->id], tex->tex_x, tex_y);
		buffer_mlx_pixel_put(vars->buffer, x, i, color);
		i++;
	}
	while (i < HEIGHT)
		buffer_mlx_pixel_put(vars->buffer, x, i++, tex->floor_color);
}

void	draw(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->buffer->img, 0, 0);
}
