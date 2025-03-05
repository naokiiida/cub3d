/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naokiiida <naokiiida@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:53:00 by naokiiida         #+#    #+#             */
/*   Updated: 2025/02/25 21:06:59 by niida            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 壁に当たったか判定
static bool	is_hit_wall(int **map, t_grid grid)
{
	if (map[grid.x][grid.y] != MAP_BLANK)
		return (true);
	return (false);
}

// DDAアルゴリズムによる壁の衝突判定
// 現在地のrayの次の整数座標までの値を追加する
void	perform_dda(t_ray *ray, int **map)
{
	while (!is_hit_wall(map, ray->grid))
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->grid.x += ray->step.x;
			ray->side = X_AXIS;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->grid.y += ray->step.y;
			ray->side = Y_AXIS;
		}
	}
}

// フレームごとに描画を更新する関数
// x方向にrayを飛ばす
// rayの初期化
// DDAによる壁の衝突判定
// 壁までの距離を計算
// 描画する壁の大きさの判定
// 壁のテクスチャ判定
// ヒットした壁のローカル座標を特定
// 描画バッファに壁を描画
int	raycasting(t_vars *vars)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		init_ray(vars, x);
		perform_dda(vars->ray, vars->map);
		calculate_perp_wall_dist(vars->ray);
		calculate_wall_size(vars->ray, vars->texture);
		decide_draw_texture(vars->ray, vars->texture);
		vars->texture->tex_x = get_texture_x(vars->ray, vars->player);
		draw_buffer(vars, x);
	}
	draw(vars);
	return (0);
}
