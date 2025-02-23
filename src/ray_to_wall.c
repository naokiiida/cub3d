/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:53:00 by naokiiida         #+#    #+#             */
/*   Updated: 2025/02/23 19:54:48 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 壁までの距離を計算
void	calculate_perp_wall_dist(t_ray *ray)
{
	if (ray->side == X_AXIS)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

// 描画する壁の大きさの判定
void	calculate_wall_size(t_ray *ray, t_texture *texture)
{
	int	line_height;

	line_height = (int)(HEIGHT / ray->perp_wall_dist);
	texture->draw_start = -line_height / 2 + HEIGHT / 2;
	if (texture->draw_start < 0)
		texture->draw_start = 0;
	texture->draw_end = line_height / 2 + HEIGHT / 2;
	if (texture->draw_end >= HEIGHT)
		texture->draw_end = HEIGHT - 1;
	// 画面ピクセルあたりのテクスチャ座標の増分を計算
	texture->step = 1.0 * TEXTURE_HEIGHT / line_height;
	texture->line_height = line_height;
}

// 壁の東西南北のテクスチャの決定
void	decide_draw_texture(t_ray *ray, t_texture *texture)
{
	if (ray->side == X_AXIS)
	{
		if (ray->dir.x < 0)
			texture->id = WEST_WALL;
		else
			texture->id = EAST_WALL;
	}
	else
	{
		if (ray->dir.y < 0)
			texture->id = NORTH_WALL;
		else
			texture->id = SOUTH_WALL;
	}
}

// ヒットしたx座標を特定
static double	get_wall_x(t_ray *ray, t_player *player)
{
	double	wall_x;

	if (ray->side == X_AXIS)
		wall_x = (player->pos.y + ray->perp_wall_dist * ray->dir.y);
	else
		wall_x = (player->pos.x + ray->perp_wall_dist * ray->dir.x);
	wall_x -= floor(wall_x);
	assert(wall_x >= 0.0);
	assert(wall_x <= 1.0);
	return (wall_x);
}

// ヒットした壁のローカル座標を特定
int	get_texture_x(t_ray *ray, t_player *player)
{
	int		tex_x;
	double	wall_x;

	wall_x = get_wall_x(ray, player);
	tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if (ray->side == X_AXIS && ray->dir.x > 0)
		tex_x = TEXTURE_WIDTH - tex_x - 1;
	if (ray->side == Y_AXIS && ray->dir.y < 0)
		tex_x = TEXTURE_WIDTH - tex_x - 1;
	return (tex_x);
}
