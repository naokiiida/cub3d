/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasano <shunkotkg0141@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:36:24 by sasano            #+#    #+#             */
/*   Updated: 2025/02/14 18:31:24 by sasano           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// テクスチャのピクセルデータを取得する関数
unsigned int get_pixel_color(t_buffer *buffer, int x, int y, t_texture *texture)
{
    char    *dst;

    dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    return *(unsigned int*)dst;
}


// 指定したピクセル位置に色を設定する関数
void    buffer_mlx_pixel_put(t_buffer *buffer, int x, int y, int color)
{
    char    *dst;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = buffer->addr + (y * buffer->line_length + x * (buffer->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}
    
// 描画バッファに壁を描画
void draw_buffer(t_vars *vars, int x)
{
    int y;
    int color;
    int i;

    i = 0;
    while (i < vars->ray->draw_start)
    {
        buffer_mlx_pixel_put(vars, x, i, 0x000000);
        i++;
    }
    while (i < vars->ray->draw_end)
    {
        color = get_texture_color(vars->texture, vars->ray);
        buffer_mlx_pixel_put(vars, x, i, color);
        i++;
    }
    while (i < HEIGHT)
    {
        buffer_mlx_pixel_put(vars, x, i, 0x000000);
        i++;
    }
}

// 描画バッファを画面に描画
void   draw(t_vars *vars)
{
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
}
